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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  get_work_pool_id (struct work_struct*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  set_work_pool_and_clear_pending (struct work_struct*,int /*<<< orphan*/ ) ; 
 int try_to_grab_pending (struct work_struct*,int,unsigned long*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool __cancel_work(struct work_struct *work, bool is_dwork)
{
	unsigned long flags;
	int ret;

	do {
		ret = try_to_grab_pending(work, is_dwork, &flags);
	} while (unlikely(ret == -EAGAIN));

	if (unlikely(ret < 0))
		return false;

	set_work_pool_and_clear_pending(work, get_work_pool_id(work));
	local_irq_restore(flags);
	return ret;
}