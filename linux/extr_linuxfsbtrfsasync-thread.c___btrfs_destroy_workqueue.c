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
struct __btrfs_workqueue {int /*<<< orphan*/  normal_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct __btrfs_workqueue*) ; 
 int /*<<< orphan*/  trace_btrfs_workqueue_destroy (struct __btrfs_workqueue*) ; 

__attribute__((used)) static inline void
__btrfs_destroy_workqueue(struct __btrfs_workqueue *wq)
{
	destroy_workqueue(wq->normal_wq);
	trace_btrfs_workqueue_destroy(wq);
	kfree(wq);
}