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
struct comedi_device {struct apci3120_private* private; } ;
struct apci3120_private {unsigned int osc_base; } ;

/* Variables and functions */
#define  CMDF_ROUND_DOWN 130 
 unsigned int CMDF_ROUND_MASK ; 
#define  CMDF_ROUND_NEAREST 129 
#define  CMDF_ROUND_UP 128 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int apci3120_ns_to_timer(struct comedi_device *dev,
					 unsigned int timer,
					 unsigned int ns,
					 unsigned int flags)
{
	struct apci3120_private *devpriv = dev->private;
	unsigned int prescale = (timer == 0) ? 10 : 1000;
	unsigned int timer_base = devpriv->osc_base * prescale;
	unsigned int divisor;

	switch (flags & CMDF_ROUND_MASK) {
	case CMDF_ROUND_UP:
		divisor = DIV_ROUND_UP(ns, timer_base);
		break;
	case CMDF_ROUND_DOWN:
		divisor = ns / timer_base;
		break;
	case CMDF_ROUND_NEAREST:
	default:
		divisor = DIV_ROUND_CLOSEST(ns, timer_base);
		break;
	}

	if (timer == 2) {
		/* timer 2 is 24-bits */
		if (divisor > 0x00ffffff)
			divisor = 0x00ffffff;
	} else {
		/* timers 0 and 1 are 16-bits */
		if (divisor > 0xffff)
			divisor = 0xffff;
	}
	/* the timers require a minimum divisor of 2 */
	if (divisor < 2)
		divisor = 2;

	return divisor;
}