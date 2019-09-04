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
struct gb_fw_core {struct gb_connection* mgmt_connection; } ;
struct gb_connection {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct gb_fw_core* dev_get_drvdata (struct device*) ; 

struct gb_connection *to_fw_mgmt_connection(struct device *dev)
{
	struct gb_fw_core *fw_core = dev_get_drvdata(dev);

	return fw_core->mgmt_connection;
}