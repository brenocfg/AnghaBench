#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int boffset; int bfactor; int minq; int maxq; struct TYPE_3__* next; int /*<<< orphan*/  led; } ;
typedef  TYPE_1__ rule_t ;

/* Variables and functions */
 int /*<<< orphan*/  set_led (int /*<<< orphan*/ ,unsigned char) ; 

void update_leds(rule_t *rules, int q)
{
	rule_t *rule = rules;
	while (rule)
	{
		int b;
		/* offset and factore correction according to rule */
		b = ( q + rule->boffset ) * rule->bfactor;
		if ( b < 0 )
			b=0;
		if ( b > 255 )
			b=255;

		if ( q >= rule->minq && q <= rule->maxq )
			set_led(rule->led, (unsigned char)b);
		else
			set_led(rule->led, 0);

		rule = rule->next;
	}
}