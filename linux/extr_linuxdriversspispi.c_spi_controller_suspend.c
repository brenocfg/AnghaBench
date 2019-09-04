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
struct spi_controller {int /*<<< orphan*/  dev; int /*<<< orphan*/  queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int spi_stop_queue (struct spi_controller*) ; 

int spi_controller_suspend(struct spi_controller *ctlr)
{
	int ret;

	/* Basically no-ops for non-queued controllers */
	if (!ctlr->queued)
		return 0;

	ret = spi_stop_queue(ctlr);
	if (ret)
		dev_err(&ctlr->dev, "queue stop failed\n");

	return ret;
}