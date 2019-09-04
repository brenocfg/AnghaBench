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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct at86rf230_local {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_IRQ_MASK ; 
 int /*<<< orphan*/  at86rf230_debugfs_remove () ; 
 int /*<<< orphan*/  at86rf230_write_subreg (struct at86rf230_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ieee802154_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_unregister_hw (int /*<<< orphan*/ ) ; 
 struct at86rf230_local* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int at86rf230_remove(struct spi_device *spi)
{
	struct at86rf230_local *lp = spi_get_drvdata(spi);

	/* mask all at86rf230 irq's */
	at86rf230_write_subreg(lp, SR_IRQ_MASK, 0);
	ieee802154_unregister_hw(lp->hw);
	ieee802154_free_hw(lp->hw);
	at86rf230_debugfs_remove();
	dev_dbg(&spi->dev, "unregistered at86rf230\n");

	return 0;
}