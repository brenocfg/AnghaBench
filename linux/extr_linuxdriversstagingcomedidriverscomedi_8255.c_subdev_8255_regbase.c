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
struct subdev_8255_private {unsigned long regbase; } ;
struct comedi_subdevice {struct subdev_8255_private* private; } ;

/* Variables and functions */

unsigned long subdev_8255_regbase(struct comedi_subdevice *s)
{
	struct subdev_8255_private *spriv = s->private;

	return spriv->regbase;
}