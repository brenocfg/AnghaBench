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
struct rza1_swio_pin {unsigned int port; unsigned int pin; unsigned int func; int input; } ;
struct rza1_swio_entry {unsigned int npins; struct rza1_swio_pin* pins; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static inline int rza1_pinmux_get_swio(unsigned int port,
				       unsigned int pin,
				       unsigned int func,
				       const struct rza1_swio_entry *table)
{
	const struct rza1_swio_pin *swio_pin;
	unsigned int i;


	for (i = 0; i < table->npins; ++i) {
		swio_pin = &table->pins[i];
		if (swio_pin->port == port && swio_pin->pin == pin &&
		    swio_pin->func == func)
			return swio_pin->input;
	}

	return -ENOENT;
}