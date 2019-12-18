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
struct samsung_i2s_priv {int /*<<< orphan*/ * pdev_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i2s_delete_secondary_device(struct samsung_i2s_priv *priv)
{
	platform_device_unregister(priv->pdev_sec);
	priv->pdev_sec = NULL;
}