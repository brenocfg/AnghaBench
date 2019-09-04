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
struct kaweth_device {int /*<<< orphan*/  net; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int usb_reset_configuration (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kaweth_reset(struct kaweth_device *kaweth)
{
	int result;

	result = usb_reset_configuration(kaweth->dev);
	mdelay(10);

	netdev_dbg(kaweth->net, "kaweth_reset() returns %d.\n", result);

	return result;
}