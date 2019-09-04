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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIO200_ENHANCE ; 
 int /*<<< orphan*/  dio200_write8 (struct comedi_device*,int /*<<< orphan*/ ,unsigned char) ; 

void amplc_dio200_set_enhance(struct comedi_device *dev, unsigned char val)
{
	dio200_write8(dev, DIO200_ENHANCE, val);
}