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
struct rt5677_priv {scalar_t__ irq_data; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct rt5677_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rt5677_free_irq(struct i2c_client *i2c)
{
	struct rt5677_priv *rt5677 = i2c_get_clientdata(i2c);

	if (rt5677->irq_data)
		regmap_del_irq_chip(i2c->irq, rt5677->irq_data);
}