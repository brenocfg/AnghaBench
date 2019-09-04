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
struct gpio_runtime {int implementation_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmf_gpio_set_amp (struct gpio_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmf_gpio_set_headphone (struct gpio_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmf_gpio_set_lineout (struct gpio_runtime*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void pmf_gpio_all_amps_off(struct gpio_runtime *rt)
{
	int saved;

	if (unlikely(!rt)) return;
	saved = rt->implementation_private;
	pmf_gpio_set_headphone(rt, 0);
	pmf_gpio_set_amp(rt, 0);
	pmf_gpio_set_lineout(rt, 0);
	rt->implementation_private = saved;
}