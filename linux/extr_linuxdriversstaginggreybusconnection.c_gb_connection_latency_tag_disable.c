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
struct gb_host_device {int /*<<< orphan*/  dev; TYPE_1__* driver; } ;
struct gb_connection {int /*<<< orphan*/  name; struct gb_host_device* hd; int /*<<< orphan*/  hd_cport_id; } ;
struct TYPE_2__ {int (* latency_tag_disable ) (struct gb_host_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct gb_host_device*,int /*<<< orphan*/ ) ; 

void gb_connection_latency_tag_disable(struct gb_connection *connection)
{
	struct gb_host_device *hd = connection->hd;
	int ret;

	if (!hd->driver->latency_tag_disable)
		return;

	ret = hd->driver->latency_tag_disable(hd, connection->hd_cport_id);
	if (ret) {
		dev_err(&connection->hd->dev,
			"%s: failed to disable latency tag: %d\n",
			connection->name, ret);
	}
}