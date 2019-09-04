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
struct fsl_udc {scalar_t__ vbus_active; scalar_t__ softconnect; scalar_t__ driver; } ;

/* Variables and functions */

__attribute__((used)) static int can_pullup(struct fsl_udc *udc)
{
	return udc->driver && udc->softconnect && udc->vbus_active;
}