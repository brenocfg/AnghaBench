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
typedef  int u64 ;
typedef  int u32 ;
struct vgic_its {TYPE_1__* dev; } ;
typedef  int phys_addr_t ;
typedef  int /*<<< orphan*/  indirect_ptr ;
typedef  int gpa_t ;
typedef  int gfn_t ;
struct TYPE_2__ {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int BASER_ADDRESS (int) ; 
 int BIT_ULL (int) ; 
 int GENMASK_ULL (int,int) ; 
 int GITS_BASER_ENTRY_SIZE (int) ; 
 int GITS_BASER_INDIRECT ; 
 int GITS_BASER_NR_PAGES (int) ; 
 int GITS_BASER_TYPE (int) ; 
#define  GITS_BASER_TYPE_COLLECTION 129 
#define  GITS_BASER_TYPE_DEVICE 128 
 int PAGE_SHIFT ; 
 int SZ_64K ; 
 int VITS_TYPER_DEVBITS ; 
 int kvm_is_visible_gfn (int /*<<< orphan*/ ,int) ; 
 scalar_t__ kvm_read_guest_lock (int /*<<< orphan*/ ,int,int*,int) ; 
 int le64_to_cpu (int) ; 

__attribute__((used)) static bool vgic_its_check_id(struct vgic_its *its, u64 baser, u32 id,
			      gpa_t *eaddr)
{
	int l1_tbl_size = GITS_BASER_NR_PAGES(baser) * SZ_64K;
	u64 indirect_ptr, type = GITS_BASER_TYPE(baser);
	int esz = GITS_BASER_ENTRY_SIZE(baser);
	int index;
	gfn_t gfn;

	switch (type) {
	case GITS_BASER_TYPE_DEVICE:
		if (id >= BIT_ULL(VITS_TYPER_DEVBITS))
			return false;
		break;
	case GITS_BASER_TYPE_COLLECTION:
		/* as GITS_TYPER.CIL == 0, ITS supports 16-bit collection ID */
		if (id >= BIT_ULL(16))
			return false;
		break;
	default:
		return false;
	}

	if (!(baser & GITS_BASER_INDIRECT)) {
		phys_addr_t addr;

		if (id >= (l1_tbl_size / esz))
			return false;

		addr = BASER_ADDRESS(baser) + id * esz;
		gfn = addr >> PAGE_SHIFT;

		if (eaddr)
			*eaddr = addr;
		return kvm_is_visible_gfn(its->dev->kvm, gfn);
	}

	/* calculate and check the index into the 1st level */
	index = id / (SZ_64K / esz);
	if (index >= (l1_tbl_size / sizeof(u64)))
		return false;

	/* Each 1st level entry is represented by a 64-bit value. */
	if (kvm_read_guest_lock(its->dev->kvm,
			   BASER_ADDRESS(baser) + index * sizeof(indirect_ptr),
			   &indirect_ptr, sizeof(indirect_ptr)))
		return false;

	indirect_ptr = le64_to_cpu(indirect_ptr);

	/* check the valid bit of the first level entry */
	if (!(indirect_ptr & BIT_ULL(63)))
		return false;

	/*
	 * Mask the guest physical address and calculate the frame number.
	 * Any address beyond our supported 48 bits of PA will be caught
	 * by the actual check in the final step.
	 */
	indirect_ptr &= GENMASK_ULL(51, 16);

	/* Find the address of the actual entry */
	index = id % (SZ_64K / esz);
	indirect_ptr += index * esz;
	gfn = indirect_ptr >> PAGE_SHIFT;

	if (eaddr)
		*eaddr = indirect_ptr;
	return kvm_is_visible_gfn(its->dev->kvm, gfn);
}