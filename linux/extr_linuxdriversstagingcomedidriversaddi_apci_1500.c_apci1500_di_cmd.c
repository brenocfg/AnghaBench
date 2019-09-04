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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inttrig; } ;

/* Variables and functions */
 int /*<<< orphan*/  apci1500_di_inttrig_start ; 

__attribute__((used)) static int apci1500_di_cmd(struct comedi_device *dev,
			   struct comedi_subdevice *s)
{
	s->async->inttrig = apci1500_di_inttrig_start;

	return 0;
}