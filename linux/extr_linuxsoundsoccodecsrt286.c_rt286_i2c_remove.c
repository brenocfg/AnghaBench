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
struct rt286_priv {int dummy; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct rt286_priv*) ; 
 struct rt286_priv* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int rt286_i2c_remove(struct i2c_client *i2c)
{
	struct rt286_priv *rt286 = i2c_get_clientdata(i2c);

	if (i2c->irq)
		free_irq(i2c->irq, rt286);

	return 0;
}