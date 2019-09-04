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
struct TYPE_2__ {int /*<<< orphan*/  build_lock; } ;

/* Variables and functions */
 TYPE_1__* NM_I (struct f2fs_sb_info*) ; 
 int __f2fs_build_free_nids (struct f2fs_sb_info*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int f2fs_build_free_nids(struct f2fs_sb_info *sbi, bool sync, bool mount)
{
	int ret;

	mutex_lock(&NM_I(sbi)->build_lock);
	ret = __f2fs_build_free_nids(sbi, sync, mount);
	mutex_unlock(&NM_I(sbi)->build_lock);

	return ret;
}