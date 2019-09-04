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
typedef  int /*<<< orphan*/  vhost_work_fn_t ;
struct vhost_work {int /*<<< orphan*/  fn; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VHOST_WORK_QUEUED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vhost_work_init(struct vhost_work *work, vhost_work_fn_t fn)
{
	clear_bit(VHOST_WORK_QUEUED, &work->flags);
	work->fn = fn;
}