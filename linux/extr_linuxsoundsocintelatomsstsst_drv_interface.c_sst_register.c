#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 TYPE_1__ sst_dsp_device ; 
 int sst_register_dsp (TYPE_1__*) ; 

int sst_register(struct device *dev)
{
	int ret_val;

	sst_dsp_device.dev = dev;
	ret_val = sst_register_dsp(&sst_dsp_device);
	if (ret_val)
		dev_err(dev, "Unable to register DSP with platform driver\n");

	return ret_val;
}