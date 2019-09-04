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
struct es7241_data {int /*<<< orphan*/  reset; int /*<<< orphan*/  m1; int /*<<< orphan*/  m0; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void es7241_set_mode(struct es7241_data *priv,  int m0, int m1)
{
	/* put the device in reset */
	gpiod_set_value_cansleep(priv->reset, 0);

	/* set the mode */
	gpiod_set_value_cansleep(priv->m0, m0);
	gpiod_set_value_cansleep(priv->m1, m1);

	/* take the device out of reset - datasheet does not specify a delay */
	gpiod_set_value_cansleep(priv->reset, 1);
}