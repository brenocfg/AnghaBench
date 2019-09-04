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
struct vt_event_wait {int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  vt_event_waitqueue ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __vt_event_wait(struct vt_event_wait *vw)
{
	/* Wait for it to pass */
	wait_event_interruptible(vt_event_waitqueue, vw->done);
}