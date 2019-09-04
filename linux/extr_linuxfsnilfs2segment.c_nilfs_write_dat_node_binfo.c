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
struct nilfs_binfo_dat {int dummy; } ;
union nilfs_binfo {struct nilfs_binfo_dat bi_dat; } ;
struct nilfs_segsum_pointer {int dummy; } ;
struct nilfs_sc_info {int dummy; } ;

/* Variables and functions */
 struct nilfs_binfo_dat* nilfs_segctor_map_segsum_entry (struct nilfs_sc_info*,struct nilfs_segsum_pointer*,int) ; 

__attribute__((used)) static void nilfs_write_dat_node_binfo(struct nilfs_sc_info *sci,
				       struct nilfs_segsum_pointer *ssp,
				       union nilfs_binfo *binfo)
{
	struct nilfs_binfo_dat *binfo_dat =
		nilfs_segctor_map_segsum_entry(sci, ssp, sizeof(*binfo_dat));
	*binfo_dat = binfo->bi_dat;
}