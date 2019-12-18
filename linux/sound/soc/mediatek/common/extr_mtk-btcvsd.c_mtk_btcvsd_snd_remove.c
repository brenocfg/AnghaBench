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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mtk_btcvsd_snd {int /*<<< orphan*/  bt_sram_bank2_base; int /*<<< orphan*/  bt_pkv_base; } ;

/* Variables and functions */
 struct mtk_btcvsd_snd* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_btcvsd_snd_remove(struct platform_device *pdev)
{
	struct mtk_btcvsd_snd *btcvsd = dev_get_drvdata(&pdev->dev);

	iounmap(btcvsd->bt_pkv_base);
	iounmap(btcvsd->bt_sram_bank2_base);
	return 0;
}