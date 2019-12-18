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
struct platform_device {int dummy; } ;
struct adm6996_priv {scalar_t__ model; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ADM6996L ; 
 scalar_t__ ADM6996M ; 
 struct adm6996_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_switch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adm6996_gpio_remove(struct platform_device *pdev)
{
	struct adm6996_priv *priv = platform_get_drvdata(pdev);

	if (priv && (priv->model == ADM6996M || priv->model == ADM6996L))
		unregister_switch(&priv->dev);

	return 0;
}