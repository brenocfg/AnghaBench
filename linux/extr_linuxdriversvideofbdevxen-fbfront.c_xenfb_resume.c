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
struct xenfb_info {int /*<<< orphan*/  fb_info; } ;
struct xenbus_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct xenfb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int xenfb_connect_backend (struct xenbus_device*,struct xenfb_info*) ; 
 int /*<<< orphan*/  xenfb_disconnect_backend (struct xenfb_info*) ; 
 int /*<<< orphan*/  xenfb_init_shared_page (struct xenfb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xenfb_resume(struct xenbus_device *dev)
{
	struct xenfb_info *info = dev_get_drvdata(&dev->dev);

	xenfb_disconnect_backend(info);
	xenfb_init_shared_page(info, info->fb_info);
	return xenfb_connect_backend(dev, info);
}