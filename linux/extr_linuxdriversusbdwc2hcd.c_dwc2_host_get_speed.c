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
struct urb {TYPE_1__* dev; } ;
struct dwc2_hsotg {int dummy; } ;
struct TYPE_2__ {int speed; } ;

/* Variables and functions */

int dwc2_host_get_speed(struct dwc2_hsotg *hsotg, void *context)
{
	struct urb *urb = context;

	return urb->dev->speed;
}