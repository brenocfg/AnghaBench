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
typedef  int /*<<< orphan*/  u16 ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s626_set_mode_a (struct comedi_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_set_mode_b (struct comedi_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s626_set_mode(struct comedi_device *dev,
			  unsigned int chan,
			  u16 setup, u16 disable_int_src)
{
	if (chan < 3)
		s626_set_mode_a(dev, chan, setup, disable_int_src);
	else
		s626_set_mode_b(dev, chan, setup, disable_int_src);
}