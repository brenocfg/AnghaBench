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
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {long* nid_cnt; } ;

/* Variables and functions */
 size_t FREE_NID ; 
 long MAX_FREE_NIDS ; 
 TYPE_1__* NM_I (struct f2fs_sb_info*) ; 

__attribute__((used)) static unsigned long __count_free_nids(struct f2fs_sb_info *sbi)
{
	long count = NM_I(sbi)->nid_cnt[FREE_NID] - MAX_FREE_NIDS;

	return count > 0 ? count : 0;
}