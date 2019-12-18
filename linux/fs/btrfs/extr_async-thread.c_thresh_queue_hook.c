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
struct __btrfs_workqueue {scalar_t__ thresh; int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 scalar_t__ NO_THRESHOLD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void thresh_queue_hook(struct __btrfs_workqueue *wq)
{
	if (wq->thresh == NO_THRESHOLD)
		return;
	atomic_inc(&wq->pending);
}