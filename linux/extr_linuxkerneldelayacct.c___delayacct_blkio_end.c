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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {struct task_delay_info* delays; } ;
struct task_delay_info {int flags; int /*<<< orphan*/  blkio_start; int /*<<< orphan*/  lock; int /*<<< orphan*/  blkio_count; int /*<<< orphan*/  blkio_delay; int /*<<< orphan*/  swapin_count; int /*<<< orphan*/  swapin_delay; } ;

/* Variables and functions */
 int DELAYACCT_PF_SWAPIN ; 
 int /*<<< orphan*/  delayacct_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void __delayacct_blkio_end(struct task_struct *p)
{
	struct task_delay_info *delays = p->delays;
	u64 *total;
	u32 *count;

	if (p->delays->flags & DELAYACCT_PF_SWAPIN) {
		total = &delays->swapin_delay;
		count = &delays->swapin_count;
	} else {
		total = &delays->blkio_delay;
		count = &delays->blkio_count;
	}

	delayacct_end(&delays->lock, &delays->blkio_start, total, count);
}