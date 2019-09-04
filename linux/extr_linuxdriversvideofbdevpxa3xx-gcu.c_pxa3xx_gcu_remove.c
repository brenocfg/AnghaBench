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
struct pxa3xx_gcu_priv {int /*<<< orphan*/  shared_phys; int /*<<< orphan*/  shared; int /*<<< orphan*/  misc_dev; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHARED_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 struct pxa3xx_gcu_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pxa3xx_gcu_free_buffers (struct device*,struct pxa3xx_gcu_priv*) ; 
 int /*<<< orphan*/  pxa3xx_gcu_wait_idle (struct pxa3xx_gcu_priv*) ; 

__attribute__((used)) static int pxa3xx_gcu_remove(struct platform_device *pdev)
{
	struct pxa3xx_gcu_priv *priv = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;

	pxa3xx_gcu_wait_idle(priv);
	misc_deregister(&priv->misc_dev);
	dma_free_coherent(dev, SHARED_SIZE, priv->shared, priv->shared_phys);
	pxa3xx_gcu_free_buffers(dev, priv);

	return 0;
}