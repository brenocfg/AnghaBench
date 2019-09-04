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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int readl (scalar_t__) ; 

__attribute__((used)) static int apci3xxx_ai_started(struct comedi_device *dev)
{
	if ((readl(dev->mmio + 8) & 0x80000) == 0x80000)
		return 1;

	return 0;
}