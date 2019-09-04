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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8996_IM_IRQ ; 
 int /*<<< orphan*/  WM8996_INTERRUPT_CONTROL ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8996_remove(struct snd_soc_component *component)
{
	struct i2c_client *i2c = to_i2c_client(component->dev);

	snd_soc_component_update_bits(component, WM8996_INTERRUPT_CONTROL,
			    WM8996_IM_IRQ, WM8996_IM_IRQ);

	if (i2c->irq)
		free_irq(i2c->irq, component);
}