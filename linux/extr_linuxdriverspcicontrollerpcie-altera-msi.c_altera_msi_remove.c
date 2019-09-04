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
struct altera_msi {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSI_INTMASK ; 
 int /*<<< orphan*/  altera_free_domains (struct altera_msi*) ; 
 int /*<<< orphan*/  irq_set_chained_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_handler_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_writel (struct altera_msi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct altera_msi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int altera_msi_remove(struct platform_device *pdev)
{
	struct altera_msi *msi = platform_get_drvdata(pdev);

	msi_writel(msi, 0, MSI_INTMASK);
	irq_set_chained_handler(msi->irq, NULL);
	irq_set_handler_data(msi->irq, NULL);

	altera_free_domains(msi);

	platform_set_drvdata(pdev, NULL);
	return 0;
}