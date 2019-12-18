#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sit_info {int /*<<< orphan*/  sentry_lock; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_4__ {TYPE_1__* v_ops; } ;
struct TYPE_3__ {int (* get_victim ) (struct f2fs_sb_info*,unsigned int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__* DIRTY_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  LFS ; 
 int /*<<< orphan*/  NO_CHECK_TYPE ; 
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int stub1 (struct f2fs_sb_info*,unsigned int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __get_victim(struct f2fs_sb_info *sbi, unsigned int *victim,
			int gc_type)
{
	struct sit_info *sit_i = SIT_I(sbi);
	int ret;

	down_write(&sit_i->sentry_lock);
	ret = DIRTY_I(sbi)->v_ops->get_victim(sbi, victim, gc_type,
					      NO_CHECK_TYPE, LFS);
	up_write(&sit_i->sentry_lock);
	return ret;
}