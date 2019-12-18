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
struct clock_event_device {int features; scalar_t__ rating; } ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_C3STOP ; 
 int CLOCK_EVT_FEAT_DUMMY ; 
 int CLOCK_EVT_FEAT_ONESHOT ; 
 int CLOCK_EVT_FEAT_PERCPU ; 
 scalar_t__ TICKDEV_MODE_ONESHOT ; 
 TYPE_1__ tick_broadcast_device ; 

__attribute__((used)) static bool tick_check_broadcast_device(struct clock_event_device *curdev,
					struct clock_event_device *newdev)
{
	if ((newdev->features & CLOCK_EVT_FEAT_DUMMY) ||
	    (newdev->features & CLOCK_EVT_FEAT_PERCPU) ||
	    (newdev->features & CLOCK_EVT_FEAT_C3STOP))
		return false;

	if (tick_broadcast_device.mode == TICKDEV_MODE_ONESHOT &&
	    !(newdev->features & CLOCK_EVT_FEAT_ONESHOT))
		return false;

	return !curdev || newdev->rating > curdev->rating;
}