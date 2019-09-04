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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct dasd_block {TYPE_1__ profile; int /*<<< orphan*/  timer; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  ccw_queue; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  tasklet_scheduled; int /*<<< orphan*/  open_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dasd_block* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dasd_block_tasklet ; 
 int /*<<< orphan*/  dasd_block_timeout ; 
 struct dasd_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct dasd_block *dasd_alloc_block(void)
{
	struct dasd_block *block;

	block = kzalloc(sizeof(*block), GFP_ATOMIC);
	if (!block)
		return ERR_PTR(-ENOMEM);
	/* open_count = 0 means device online but not in use */
	atomic_set(&block->open_count, -1);

	atomic_set(&block->tasklet_scheduled, 0);
	tasklet_init(&block->tasklet, dasd_block_tasklet,
		     (unsigned long) block);
	INIT_LIST_HEAD(&block->ccw_queue);
	spin_lock_init(&block->queue_lock);
	timer_setup(&block->timer, dasd_block_timeout, 0);
	spin_lock_init(&block->profile.lock);

	return block;
}