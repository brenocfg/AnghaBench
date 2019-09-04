#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gb_control {TYPE_2__* connection; } ;
struct TYPE_4__ {TYPE_1__* intf; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gb_connection_enable_tx (TYPE_2__*) ; 

int gb_control_resume(struct gb_control *control)
{
	int ret;

	ret = gb_connection_enable_tx(control->connection);
	if (ret) {
		dev_err(&control->connection->intf->dev,
			"failed to enable control connection: %d\n", ret);
		return ret;
	}

	return 0;
}