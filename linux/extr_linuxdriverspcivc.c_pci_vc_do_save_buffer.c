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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ data; } ;
struct pci_cap_saved_state {TYPE_1__ cap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PCI_CAP_VC_PER_VC_SIZEOF ; 
 int PCI_VC_CAP1_ARB_SIZE ; 
 int PCI_VC_CAP1_EVCC ; 
 int PCI_VC_CAP1_LPEVCC ; 
 int PCI_VC_CAP2_128_PHASE ; 
 int PCI_VC_CAP2_32_PHASE ; 
 int PCI_VC_CAP2_64_PHASE ; 
 int PCI_VC_CAP2_ARB_OFF ; 
 int PCI_VC_PORT_CAP1 ; 
 int PCI_VC_PORT_CAP2 ; 
 scalar_t__ PCI_VC_PORT_CTRL ; 
 int PCI_VC_RES_CAP ; 
 int PCI_VC_RES_CAP_128_PHASE ; 
 int PCI_VC_RES_CAP_128_PHASE_TB ; 
 int PCI_VC_RES_CAP_256_PHASE ; 
 int PCI_VC_RES_CAP_32_PHASE ; 
 int PCI_VC_RES_CAP_64_PHASE ; 
 int PCI_VC_RES_CAP_ARB_OFF ; 
 int PCI_VC_RES_CTRL ; 
 int PCI_VC_RES_CTRL_ARB_SELECT ; 
 int PCI_VC_RES_CTRL_ENABLE ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_vc_enable (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_vc_load_arb_table (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_vc_load_port_arb_table (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_vc_save_restore_dwords (struct pci_dev*,int,int*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_vc_do_save_buffer(struct pci_dev *dev, int pos,
				 struct pci_cap_saved_state *save_state,
				 bool save)
{
	u32 cap1;
	char evcc, lpevcc, parb_size;
	int i, len = 0;
	u8 *buf = save_state ? (u8 *)save_state->cap.data : NULL;

	/* Sanity check buffer size for save/restore */
	if (buf && save_state->cap.size !=
	    pci_vc_do_save_buffer(dev, pos, NULL, save)) {
		pci_err(dev, "VC save buffer size does not match @0x%x\n", pos);
		return -ENOMEM;
	}

	pci_read_config_dword(dev, pos + PCI_VC_PORT_CAP1, &cap1);
	/* Extended VC Count (not counting VC0) */
	evcc = cap1 & PCI_VC_CAP1_EVCC;
	/* Low Priority Extended VC Count (not counting VC0) */
	lpevcc = (cap1 & PCI_VC_CAP1_LPEVCC) >> 4;
	/* Port Arbitration Table Entry Size (bits) */
	parb_size = 1 << ((cap1 & PCI_VC_CAP1_ARB_SIZE) >> 10);

	/*
	 * Port VC Control Register contains VC Arbitration Select, which
	 * cannot be modified when more than one LPVC is in operation.  We
	 * therefore save/restore it first, as only VC0 should be enabled
	 * after device reset.
	 */
	if (buf) {
		if (save)
			pci_read_config_word(dev, pos + PCI_VC_PORT_CTRL,
					     (u16 *)buf);
		else
			pci_write_config_word(dev, pos + PCI_VC_PORT_CTRL,
					      *(u16 *)buf);
		buf += 4;
	}
	len += 4;

	/*
	 * If we have any Low Priority VCs and a VC Arbitration Table Offset
	 * in Port VC Capability Register 2 then save/restore it next.
	 */
	if (lpevcc) {
		u32 cap2;
		int vcarb_offset;

		pci_read_config_dword(dev, pos + PCI_VC_PORT_CAP2, &cap2);
		vcarb_offset = ((cap2 & PCI_VC_CAP2_ARB_OFF) >> 24) * 16;

		if (vcarb_offset) {
			int size, vcarb_phases = 0;

			if (cap2 & PCI_VC_CAP2_128_PHASE)
				vcarb_phases = 128;
			else if (cap2 & PCI_VC_CAP2_64_PHASE)
				vcarb_phases = 64;
			else if (cap2 & PCI_VC_CAP2_32_PHASE)
				vcarb_phases = 32;

			/* Fixed 4 bits per phase per lpevcc (plus VC0) */
			size = ((lpevcc + 1) * vcarb_phases * 4) / 8;

			if (size && buf) {
				pci_vc_save_restore_dwords(dev,
							   pos + vcarb_offset,
							   (u32 *)buf,
							   size / 4, save);
				/*
				 * On restore, we need to signal hardware to
				 * re-load the VC Arbitration Table.
				 */
				if (!save)
					pci_vc_load_arb_table(dev, pos);

				buf += size;
			}
			len += size;
		}
	}

	/*
	 * In addition to each VC Resource Control Register, we may have a
	 * Port Arbitration Table attached to each VC.  The Port Arbitration
	 * Table Offset in each VC Resource Capability Register tells us if
	 * it exists.  The entry size is global from the Port VC Capability
	 * Register1 above.  The number of phases is determined per VC.
	 */
	for (i = 0; i < evcc + 1; i++) {
		u32 cap;
		int parb_offset;

		pci_read_config_dword(dev, pos + PCI_VC_RES_CAP +
				      (i * PCI_CAP_VC_PER_VC_SIZEOF), &cap);
		parb_offset = ((cap & PCI_VC_RES_CAP_ARB_OFF) >> 24) * 16;
		if (parb_offset) {
			int size, parb_phases = 0;

			if (cap & PCI_VC_RES_CAP_256_PHASE)
				parb_phases = 256;
			else if (cap & (PCI_VC_RES_CAP_128_PHASE |
					PCI_VC_RES_CAP_128_PHASE_TB))
				parb_phases = 128;
			else if (cap & PCI_VC_RES_CAP_64_PHASE)
				parb_phases = 64;
			else if (cap & PCI_VC_RES_CAP_32_PHASE)
				parb_phases = 32;

			size = (parb_size * parb_phases) / 8;

			if (size && buf) {
				pci_vc_save_restore_dwords(dev,
							   pos + parb_offset,
							   (u32 *)buf,
							   size / 4, save);
				buf += size;
			}
			len += size;
		}

		/* VC Resource Control Register */
		if (buf) {
			int ctrl_pos = pos + PCI_VC_RES_CTRL +
						(i * PCI_CAP_VC_PER_VC_SIZEOF);
			if (save)
				pci_read_config_dword(dev, ctrl_pos,
						      (u32 *)buf);
			else {
				u32 tmp, ctrl = *(u32 *)buf;
				/*
				 * For an FLR case, the VC config may remain.
				 * Preserve enable bit, restore the rest.
				 */
				pci_read_config_dword(dev, ctrl_pos, &tmp);
				tmp &= PCI_VC_RES_CTRL_ENABLE;
				tmp |= ctrl & ~PCI_VC_RES_CTRL_ENABLE;
				pci_write_config_dword(dev, ctrl_pos, tmp);
				/* Load port arbitration table if used */
				if (ctrl & PCI_VC_RES_CTRL_ARB_SELECT)
					pci_vc_load_port_arb_table(dev, pos, i);
				/* Re-enable if needed */
				if ((ctrl ^ tmp) & PCI_VC_RES_CTRL_ENABLE)
					pci_vc_enable(dev, pos, i);
			}
			buf += 4;
		}
		len += 4;
	}

	return buf ? 0 : len;
}