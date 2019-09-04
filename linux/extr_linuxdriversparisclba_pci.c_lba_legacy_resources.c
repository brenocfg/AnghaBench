#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {char* name; int start; int end; int /*<<< orphan*/  flags; } ;
struct parisc_device {int dummy; } ;
struct TYPE_2__ {char* lmmio_name; char* elmmio_name; char* io_name; int /*<<< orphan*/  hba_num; scalar_t__ base_addr; struct resource bus_num; struct resource io_space; struct resource elmmio_space; struct resource lmmio_space; int /*<<< orphan*/  lmmio_space_offset; } ;
struct lba_device {TYPE_1__ hba; } ;

/* Variables and functions */
 int HBA_PORT_BASE (int /*<<< orphan*/ ) ; 
 int HBA_PORT_SPACE_SIZE ; 
 int /*<<< orphan*/  IORESOURCE_BUS ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ LBA_FW_SCRATCH ; 
 scalar_t__ LBA_IOS_BASE ; 
 scalar_t__ LBA_IOS_MASK ; 
 int /*<<< orphan*/  PCI_F_EXTEND ; 
 int READ_REG32 (scalar_t__) ; 
 int /*<<< orphan*/  sba_directed_lmmio (struct parisc_device*,struct resource*) ; 
 int /*<<< orphan*/  sba_distributed_lmmio (struct parisc_device*,struct resource*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void
lba_legacy_resources(struct parisc_device *pa_dev, struct lba_device *lba_dev)
{
	struct resource *r;
	int lba_num;

	lba_dev->hba.lmmio_space_offset = PCI_F_EXTEND;

	/*
	** With "legacy" firmware, the lowest byte of FW_SCRATCH
	** represents bus->secondary and the second byte represents
	** bus->subsidiary (i.e. highest PPB programmed by firmware).
	** PCI bus walk *should* end up with the same result.
	** FIXME: But we don't have sanity checks in PCI or LBA.
	*/
	lba_num = READ_REG32(lba_dev->hba.base_addr + LBA_FW_SCRATCH);
	r = &(lba_dev->hba.bus_num);
	r->name = "LBA PCI Busses";
	r->start = lba_num & 0xff;
	r->end = (lba_num>>8) & 0xff;
	r->flags = IORESOURCE_BUS;

	/* Set up local PCI Bus resources - we don't need them for
	** Legacy boxes but it's nice to see in /proc/iomem.
	*/
	r = &(lba_dev->hba.lmmio_space);
	sprintf(lba_dev->hba.lmmio_name, "PCI%02x LMMIO",
					(int)lba_dev->hba.bus_num.start);
	r->name  = lba_dev->hba.lmmio_name;

#if 1
	/* We want the CPU -> IO routing of addresses.
	 * The SBA BASE/MASK registers control CPU -> IO routing.
	 * Ask SBA what is routed to this rope/LBA.
	 */
	sba_distributed_lmmio(pa_dev, r);
#else
	/*
	 * The LBA BASE/MASK registers control IO -> System routing.
	 *
	 * The following code works but doesn't get us what we want.
	 * Well, only because firmware (v5.0) on C3000 doesn't program
	 * the LBA BASE/MASE registers to be the exact inverse of 
	 * the corresponding SBA registers. Other Astro/Pluto
	 * based platform firmware may do it right.
	 *
	 * Should someone want to mess with MSI, they may need to
	 * reprogram LBA BASE/MASK registers. Thus preserve the code
	 * below until MSI is known to work on C3000/A500/N4000/RP3440.
	 *
	 * Using the code below, /proc/iomem shows:
	 * ...
	 * f0000000-f0ffffff : PCI00 LMMIO
	 *   f05d0000-f05d0000 : lcd_data
	 *   f05d0008-f05d0008 : lcd_cmd
	 * f1000000-f1ffffff : PCI01 LMMIO
	 * f4000000-f4ffffff : PCI02 LMMIO
	 *   f4000000-f4001fff : sym53c8xx
	 *   f4002000-f4003fff : sym53c8xx
	 *   f4004000-f40043ff : sym53c8xx
	 *   f4005000-f40053ff : sym53c8xx
	 *   f4007000-f4007fff : ohci_hcd
	 *   f4008000-f40083ff : tulip
	 * f6000000-f6ffffff : PCI03 LMMIO
	 * f8000000-fbffffff : PCI00 ELMMIO
	 *   fa100000-fa4fffff : stifb mmio
	 *   fb000000-fb1fffff : stifb fb
	 *
	 * But everything listed under PCI02 actually lives under PCI00.
	 * This is clearly wrong.
	 *
	 * Asking SBA how things are routed tells the correct story:
	 * LMMIO_BASE/MASK/ROUTE f4000001 fc000000 00000000
	 * DIR0_BASE/MASK/ROUTE fa000001 fe000000 00000006
	 * DIR1_BASE/MASK/ROUTE f9000001 ff000000 00000004
	 * DIR2_BASE/MASK/ROUTE f0000000 fc000000 00000000
	 * DIR3_BASE/MASK/ROUTE f0000000 fc000000 00000000
	 *
	 * Which looks like this in /proc/iomem:
	 * f4000000-f47fffff : PCI00 LMMIO
	 *   f4000000-f4001fff : sym53c8xx
	 *   ...[deteled core devices - same as above]...
	 *   f4008000-f40083ff : tulip
	 * f4800000-f4ffffff : PCI01 LMMIO
	 * f6000000-f67fffff : PCI02 LMMIO
	 * f7000000-f77fffff : PCI03 LMMIO
	 * f9000000-f9ffffff : PCI02 ELMMIO
	 * fa000000-fbffffff : PCI03 ELMMIO
	 *   fa100000-fa4fffff : stifb mmio
	 *   fb000000-fb1fffff : stifb fb
	 *
	 * ie all Built-in core are under now correctly under PCI00.
	 * The "PCI02 ELMMIO" directed range is for:
	 *  +-[02]---03.0  3Dfx Interactive, Inc. Voodoo 2
	 *
	 * All is well now.
	 */
	r->start = READ_REG32(lba_dev->hba.base_addr + LBA_LMMIO_BASE);
	if (r->start & 1) {
		unsigned long rsize;

		r->flags = IORESOURCE_MEM;
		/* mmio_mask also clears Enable bit */
		r->start &= mmio_mask;
		r->start = PCI_HOST_ADDR(HBA_DATA(lba_dev), r->start);
		rsize = ~ READ_REG32(lba_dev->hba.base_addr + LBA_LMMIO_MASK);

		/*
		** Each rope only gets part of the distributed range.
		** Adjust "window" for this rope.
		*/
		rsize /= ROPES_PER_IOC;
		r->start += (rsize + 1) * LBA_NUM(pa_dev->hpa.start);
		r->end = r->start + rsize;
	} else {
		r->end = r->start = 0;	/* Not enabled. */
	}
#endif

	/*
	** "Directed" ranges are used when the "distributed range" isn't
	** sufficient for all devices below a given LBA.  Typically devices
	** like graphics cards or X25 may need a directed range when the
	** bus has multiple slots (ie multiple devices) or the device
	** needs more than the typical 4 or 8MB a distributed range offers.
	**
	** The main reason for ignoring it now frigging complications.
	** Directed ranges may overlap (and have precedence) over
	** distributed ranges. Or a distributed range assigned to a unused
	** rope may be used by a directed range on a different rope.
	** Support for graphics devices may require fixing this
	** since they may be assigned a directed range which overlaps
	** an existing (but unused portion of) distributed range.
	*/
	r = &(lba_dev->hba.elmmio_space);
	sprintf(lba_dev->hba.elmmio_name, "PCI%02x ELMMIO",
					(int)lba_dev->hba.bus_num.start);
	r->name  = lba_dev->hba.elmmio_name;

#if 1
	/* See comment which precedes call to sba_directed_lmmio() */
	sba_directed_lmmio(pa_dev, r);
#else
	r->start = READ_REG32(lba_dev->hba.base_addr + LBA_ELMMIO_BASE);

	if (r->start & 1) {
		unsigned long rsize;
		r->flags = IORESOURCE_MEM;
		/* mmio_mask also clears Enable bit */
		r->start &= mmio_mask;
		r->start = PCI_HOST_ADDR(HBA_DATA(lba_dev), r->start);
		rsize = READ_REG32(lba_dev->hba.base_addr + LBA_ELMMIO_MASK);
		r->end = r->start + ~rsize;
	}
#endif

	r = &(lba_dev->hba.io_space);
	sprintf(lba_dev->hba.io_name, "PCI%02x Ports",
					(int)lba_dev->hba.bus_num.start);
	r->name  = lba_dev->hba.io_name;
	r->flags = IORESOURCE_IO;
	r->start = READ_REG32(lba_dev->hba.base_addr + LBA_IOS_BASE) & ~1L;
	r->end   = r->start + (READ_REG32(lba_dev->hba.base_addr + LBA_IOS_MASK) ^ (HBA_PORT_SPACE_SIZE - 1));

	/* Virtualize the I/O Port space ranges */
	lba_num = HBA_PORT_BASE(lba_dev->hba.hba_num);
	r->start |= lba_num;
	r->end   |= lba_num;
}