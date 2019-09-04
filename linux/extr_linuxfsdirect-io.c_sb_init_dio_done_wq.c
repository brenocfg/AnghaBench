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
struct workqueue_struct {int dummy; } ;
struct super_block {int /*<<< orphan*/  s_dio_done_wq; int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 struct workqueue_struct* alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct workqueue_struct* cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct workqueue_struct*) ; 
 int /*<<< orphan*/  destroy_workqueue (struct workqueue_struct*) ; 

int sb_init_dio_done_wq(struct super_block *sb)
{
	struct workqueue_struct *old;
	struct workqueue_struct *wq = alloc_workqueue("dio/%s",
						      WQ_MEM_RECLAIM, 0,
						      sb->s_id);
	if (!wq)
		return -ENOMEM;
	/*
	 * This has to be atomic as more DIOs can race to create the workqueue
	 */
	old = cmpxchg(&sb->s_dio_done_wq, NULL, wq);
	/* Someone created workqueue before us? Free ours... */
	if (old)
		destroy_workqueue(wq);
	return 0;
}