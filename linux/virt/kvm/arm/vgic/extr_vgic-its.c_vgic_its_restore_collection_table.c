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
typedef  int u64 ;
struct vgic_its_abi {int cte_esz; } ;
struct vgic_its {int baser_coll_table; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int GITS_BASER_ADDR_48_to_52 (int) ; 
 size_t GITS_BASER_NR_PAGES (int) ; 
 int GITS_BASER_VALID ; 
 size_t SZ_64K ; 
 struct vgic_its_abi* vgic_its_get_abi (struct vgic_its*) ; 
 int vgic_its_restore_cte (struct vgic_its*,int,int) ; 

__attribute__((used)) static int vgic_its_restore_collection_table(struct vgic_its *its)
{
	const struct vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 baser = its->baser_coll_table;
	int cte_esz = abi->cte_esz;
	size_t max_size, read = 0;
	gpa_t gpa;
	int ret;

	if (!(baser & GITS_BASER_VALID))
		return 0;

	gpa = GITS_BASER_ADDR_48_to_52(baser);

	max_size = GITS_BASER_NR_PAGES(baser) * SZ_64K;

	while (read < max_size) {
		ret = vgic_its_restore_cte(its, gpa, cte_esz);
		if (ret <= 0)
			break;
		gpa += cte_esz;
		read += cte_esz;
	}

	if (ret > 0)
		return 0;

	return ret;
}