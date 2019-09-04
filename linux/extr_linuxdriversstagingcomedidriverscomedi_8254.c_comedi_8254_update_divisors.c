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
struct comedi_8254 {int divisor; int next_div; int divisor1; int next_div1; int divisor2; int next_div2; } ;

/* Variables and functions */

void comedi_8254_update_divisors(struct comedi_8254 *i8254)
{
	/* masking is done since counter maps zero to 0x10000 */
	i8254->divisor = i8254->next_div & 0xffff;
	i8254->divisor1 = i8254->next_div1 & 0xffff;
	i8254->divisor2 = i8254->next_div2 & 0xffff;
}