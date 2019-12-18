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
struct rb4xx_nand_info {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB4XX_NAND_GPIO_ALE ; 
 int /*<<< orphan*/  RB4XX_NAND_GPIO_CLE ; 
 int /*<<< orphan*/  RB4XX_NAND_GPIO_NCE ; 
 int /*<<< orphan*/  RB4XX_NAND_GPIO_READY ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rb4xx_nand_info*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ ) ; 
 struct rb4xx_nand_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbinfo_to_mtd (struct rb4xx_nand_info*) ; 

__attribute__((used)) static int rb4xx_nand_remove(struct platform_device *pdev)
{
	struct rb4xx_nand_info *info = platform_get_drvdata(pdev);

	nand_release(rbinfo_to_mtd(info));
	platform_set_drvdata(pdev, NULL);
	kfree(info);
	gpio_free(RB4XX_NAND_GPIO_NCE);
	gpio_free(RB4XX_NAND_GPIO_CLE);
	gpio_free(RB4XX_NAND_GPIO_ALE);
	gpio_free(RB4XX_NAND_GPIO_READY);

	return 0;
}