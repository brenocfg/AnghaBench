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
struct TYPE_2__ {scalar_t__ emulate_fua_write; } ;
struct se_device {TYPE_1__ dev_attrib; } ;

/* Variables and functions */
 scalar_t__ target_check_wce (struct se_device*) ; 

bool
target_check_fua(struct se_device *dev)
{
	return target_check_wce(dev) && dev->dev_attrib.emulate_fua_write > 0;
}