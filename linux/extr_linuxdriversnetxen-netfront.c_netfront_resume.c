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
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;
struct netfront_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct netfront_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xennet_disconnect_backend (struct netfront_info*) ; 

__attribute__((used)) static int netfront_resume(struct xenbus_device *dev)
{
	struct netfront_info *info = dev_get_drvdata(&dev->dev);

	dev_dbg(&dev->dev, "%s\n", dev->nodename);

	xennet_disconnect_backend(info);
	return 0;
}