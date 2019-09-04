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
struct fuse_conn {int /*<<< orphan*/  num_waiting; int /*<<< orphan*/  blocked_waitq; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void fuse_wait_aborted(struct fuse_conn *fc)
{
	/* matches implicit memory barrier in fuse_drop_waiting() */
	smp_mb();
	wait_event(fc->blocked_waitq, atomic_read(&fc->num_waiting) == 0);
}