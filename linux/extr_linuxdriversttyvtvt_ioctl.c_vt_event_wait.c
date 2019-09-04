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
struct vt_event_wait {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vt_event_dequeue (struct vt_event_wait*) ; 
 int /*<<< orphan*/  __vt_event_queue (struct vt_event_wait*) ; 
 int /*<<< orphan*/  __vt_event_wait (struct vt_event_wait*) ; 

__attribute__((used)) static void vt_event_wait(struct vt_event_wait *vw)
{
	__vt_event_queue(vw);
	__vt_event_wait(vw);
	__vt_event_dequeue(vw);
}