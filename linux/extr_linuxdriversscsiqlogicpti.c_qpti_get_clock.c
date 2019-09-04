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
struct qlogicpti {unsigned int clock; int /*<<< orphan*/  prom_node; } ;

/* Variables and functions */
 unsigned int prom_getintdefault (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void qpti_get_clock(struct qlogicpti *qpti)
{
	unsigned int cfreq;

	/* Check for what the clock input to this card is.
	 * Default to 40Mhz.
	 */
	cfreq = prom_getintdefault(qpti->prom_node,"clock-frequency",40000000);
	qpti->clock = (cfreq + 500000)/1000000;
	if (qpti->clock == 0) /* bullshit */
		qpti->clock = 40;
}