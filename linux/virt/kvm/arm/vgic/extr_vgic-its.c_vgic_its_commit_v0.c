#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vgic_its_abi {int /*<<< orphan*/  dte_esz; int /*<<< orphan*/  cte_esz; } ;
struct vgic_its {int baser_coll_table; int baser_device_table; } ;

/* Variables and functions */
 int GIC_ENCODE_SZ (int /*<<< orphan*/ ,int) ; 
 int GITS_BASER_ENTRY_SIZE_MASK ; 
 int GITS_BASER_ENTRY_SIZE_SHIFT ; 
 struct vgic_its_abi* vgic_its_get_abi (struct vgic_its*) ; 

__attribute__((used)) static int vgic_its_commit_v0(struct vgic_its *its)
{
	const struct vgic_its_abi *abi;

	abi = vgic_its_get_abi(its);
	its->baser_coll_table &= ~GITS_BASER_ENTRY_SIZE_MASK;
	its->baser_device_table &= ~GITS_BASER_ENTRY_SIZE_MASK;

	its->baser_coll_table |= (GIC_ENCODE_SZ(abi->cte_esz, 5)
					<< GITS_BASER_ENTRY_SIZE_SHIFT);

	its->baser_device_table |= (GIC_ENCODE_SZ(abi->dte_esz, 5)
					<< GITS_BASER_ENTRY_SIZE_SHIFT);
	return 0;
}