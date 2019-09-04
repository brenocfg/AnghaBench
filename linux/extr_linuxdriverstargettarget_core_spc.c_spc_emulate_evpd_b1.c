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
struct TYPE_4__ {scalar_t__ is_nonrot; } ;
struct se_device {TYPE_2__ dev_attrib; TYPE_1__* transport; } ;
struct se_cmd {struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_3__ {unsigned char (* get_device_type ) (struct se_device*) ;} ;

/* Variables and functions */
 unsigned char stub1 (struct se_device*) ; 

__attribute__((used)) static sense_reason_t
spc_emulate_evpd_b1(struct se_cmd *cmd, unsigned char *buf)
{
	struct se_device *dev = cmd->se_dev;

	buf[0] = dev->transport->get_device_type(dev);
	buf[3] = 0x3c;
	buf[5] = dev->dev_attrib.is_nonrot ? 1 : 0;

	return 0;
}