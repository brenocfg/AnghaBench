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
struct wm8903_priv {int /*<<< orphan*/  supplies; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct wm8903_priv*) ; 
 struct wm8903_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8903_free_gpio (struct wm8903_priv*) ; 

__attribute__((used)) static int wm8903_i2c_remove(struct i2c_client *client)
{
	struct wm8903_priv *wm8903 = i2c_get_clientdata(client);

	regulator_bulk_disable(ARRAY_SIZE(wm8903->supplies),
			       wm8903->supplies);
	if (client->irq)
		free_irq(client->irq, wm8903);
	wm8903_free_gpio(wm8903);

	return 0;
}