#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mdio_mux_gpio_state {int* values; TYPE_1__* gpios; } ;
struct TYPE_2__ {unsigned int ndescs; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (unsigned int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mdio_mux_gpio_switch_fn(int current_child, int desired_child,
				   void *data)
{
	struct mdio_mux_gpio_state *s = data;
	unsigned int n;

	if (current_child == desired_child)
		return 0;

	for (n = 0; n < s->gpios->ndescs; n++)
		s->values[n] = (desired_child >> n) & 1;

	gpiod_set_array_value_cansleep(s->gpios->ndescs, s->gpios->desc,
				       s->values);

	return 0;
}