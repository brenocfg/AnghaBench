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
struct rb91x_nand_info {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ ) ; 
 struct rb91x_nand_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rbinfo_to_mtd (struct rb91x_nand_info*) ; 

__attribute__((used)) static int rb91x_nand_remove(struct platform_device *pdev)
{
	struct rb91x_nand_info *info = platform_get_drvdata(pdev);

	nand_release(rbinfo_to_mtd(info));

	return 0;
}