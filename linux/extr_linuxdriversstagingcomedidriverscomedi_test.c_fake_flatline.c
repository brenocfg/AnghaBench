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
struct comedi_device {TYPE_1__* read_subdev; } ;
struct TYPE_2__ {int maxdata; } ;

/* Variables and functions */

__attribute__((used)) static unsigned short fake_flatline(struct comedi_device *dev,
				    unsigned int range_index,
				    unsigned int current_time)
{
	return dev->read_subdev->maxdata / 2;
}