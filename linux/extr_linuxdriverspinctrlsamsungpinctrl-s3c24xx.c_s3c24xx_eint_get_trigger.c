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

/* Variables and functions */
 int EINT_EDGE_BOTH ; 
 int EINT_EDGE_FALLING ; 
 int EINT_EDGE_RISING ; 
 int EINT_LEVEL_HIGH ; 
 int EINT_LEVEL_LOW ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 

__attribute__((used)) static int s3c24xx_eint_get_trigger(unsigned int type)
{
	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		return EINT_EDGE_RISING;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		return EINT_EDGE_FALLING;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		return EINT_EDGE_BOTH;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		return EINT_LEVEL_HIGH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		return EINT_LEVEL_LOW;
		break;
	default:
		return -EINVAL;
	}
}