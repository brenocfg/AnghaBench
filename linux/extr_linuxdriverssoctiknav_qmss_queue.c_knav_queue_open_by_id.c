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
struct knav_queue_inst {int dummy; } ;
struct knav_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENODEV ; 
 struct knav_queue* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int KNAV_QUEUE_SHARED ; 
 struct knav_queue* __knav_queue_open (struct knav_queue_inst*,char const*,unsigned int) ; 
 int /*<<< orphan*/  knav_dev_lock ; 
 struct knav_queue_inst* knav_queue_find_by_id (unsigned int) ; 
 scalar_t__ knav_queue_is_busy (struct knav_queue_inst*) ; 
 int /*<<< orphan*/  knav_queue_is_shared (struct knav_queue_inst*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct knav_queue *
knav_queue_open_by_id(const char *name, unsigned id, unsigned flags)
{
	struct knav_queue_inst *inst;
	struct knav_queue *qh;

	mutex_lock(&knav_dev_lock);

	qh = ERR_PTR(-ENODEV);
	inst = knav_queue_find_by_id(id);
	if (!inst)
		goto unlock_ret;

	qh = ERR_PTR(-EEXIST);
	if (!(flags & KNAV_QUEUE_SHARED) && knav_queue_is_busy(inst))
		goto unlock_ret;

	qh = ERR_PTR(-EBUSY);
	if ((flags & KNAV_QUEUE_SHARED) &&
	    (knav_queue_is_busy(inst) && !knav_queue_is_shared(inst)))
		goto unlock_ret;

	qh = __knav_queue_open(inst, name, flags);

unlock_ret:
	mutex_unlock(&knav_dev_lock);

	return qh;
}