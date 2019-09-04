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
struct comedi_8254 {unsigned int osc_base; unsigned int next_div; } ;

/* Variables and functions */
#define  CMDF_ROUND_DOWN 130 
 unsigned int CMDF_ROUND_MASK ; 
#define  CMDF_ROUND_NEAREST 129 
#define  CMDF_ROUND_UP 128 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 unsigned int I8254_MAX_COUNT ; 

void comedi_8254_ns_to_timer(struct comedi_8254 *i8254,
			     unsigned int *nanosec, unsigned int flags)
{
	unsigned int divisor;

	switch (flags & CMDF_ROUND_MASK) {
	default:
	case CMDF_ROUND_NEAREST:
		divisor = DIV_ROUND_CLOSEST(*nanosec, i8254->osc_base);
		break;
	case CMDF_ROUND_UP:
		divisor = DIV_ROUND_UP(*nanosec, i8254->osc_base);
		break;
	case CMDF_ROUND_DOWN:
		divisor = *nanosec / i8254->osc_base;
		break;
	}
	if (divisor < 2)
		divisor = 2;
	if (divisor > I8254_MAX_COUNT)
		divisor = I8254_MAX_COUNT;

	*nanosec = divisor * i8254->osc_base;
	i8254->next_div = divisor;
}