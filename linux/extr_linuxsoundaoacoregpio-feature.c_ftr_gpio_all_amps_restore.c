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
struct gpio_runtime {int implementation_private; } ;
struct TYPE_2__ {scalar_t__ set_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftr_gpio_set_amp (struct gpio_runtime*,int) ; 
 int /*<<< orphan*/  ftr_gpio_set_headphone (struct gpio_runtime*,int) ; 
 int /*<<< orphan*/  ftr_gpio_set_lineout (struct gpio_runtime*,int) ; 
 int /*<<< orphan*/  ftr_gpio_set_master (struct gpio_runtime*,int) ; 
 TYPE_1__ methods ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ftr_gpio_all_amps_restore(struct gpio_runtime *rt)
{
	int s;

	if (unlikely(!rt)) return;
	s = rt->implementation_private;
	ftr_gpio_set_headphone(rt, (s>>0)&1);
	ftr_gpio_set_amp(rt, (s>>1)&1);
	ftr_gpio_set_lineout(rt, (s>>2)&1);
	if (methods.set_master)
		ftr_gpio_set_master(rt, (s>>3)&1);
}