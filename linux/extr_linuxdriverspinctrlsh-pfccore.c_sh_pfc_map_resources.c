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
struct sh_pfc_window {int /*<<< orphan*/  virt; int /*<<< orphan*/  size; int /*<<< orphan*/  phys; } ;
struct sh_pfc {unsigned int num_windows; unsigned int num_irqs; unsigned int* irqs; int /*<<< orphan*/  dev; struct sh_pfc_window* windows; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ ,struct resource*) ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 void* platform_get_irq (struct platform_device*,unsigned int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int sh_pfc_map_resources(struct sh_pfc *pfc,
				struct platform_device *pdev)
{
	unsigned int num_windows, num_irqs;
	struct sh_pfc_window *windows;
	unsigned int *irqs = NULL;
	struct resource *res;
	unsigned int i;
	int irq;

	/* Count the MEM and IRQ resources. */
	for (num_windows = 0;; num_windows++) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, num_windows);
		if (!res)
			break;
	}
	for (num_irqs = 0;; num_irqs++) {
		irq = platform_get_irq(pdev, num_irqs);
		if (irq == -EPROBE_DEFER)
			return irq;
		if (irq < 0)
			break;
	}

	if (num_windows == 0)
		return -EINVAL;

	/* Allocate memory windows and IRQs arrays. */
	windows = devm_kcalloc(pfc->dev, num_windows, sizeof(*windows),
			       GFP_KERNEL);
	if (windows == NULL)
		return -ENOMEM;

	pfc->num_windows = num_windows;
	pfc->windows = windows;

	if (num_irqs) {
		irqs = devm_kcalloc(pfc->dev, num_irqs, sizeof(*irqs),
				    GFP_KERNEL);
		if (irqs == NULL)
			return -ENOMEM;

		pfc->num_irqs = num_irqs;
		pfc->irqs = irqs;
	}

	/* Fill them. */
	for (i = 0; i < num_windows; i++) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, i);
		windows->phys = res->start;
		windows->size = resource_size(res);
		windows->virt = devm_ioremap_resource(pfc->dev, res);
		if (IS_ERR(windows->virt))
			return -ENOMEM;
		windows++;
	}
	for (i = 0; i < num_irqs; i++)
		*irqs++ = platform_get_irq(pdev, i);

	return 0;
}