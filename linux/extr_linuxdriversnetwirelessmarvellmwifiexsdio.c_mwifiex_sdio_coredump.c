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
struct sdio_mmc_card {int /*<<< orphan*/  work; int /*<<< orphan*/  work_flags; } ;
struct sdio_func {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWIFIEX_IFACE_WORK_DEVICE_DUMP ; 
 struct sdio_func* dev_to_sdio_func (struct device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct sdio_mmc_card* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwifiex_sdio_coredump(struct device *dev)
{
	struct sdio_func *func = dev_to_sdio_func(dev);
	struct sdio_mmc_card *card;

	card = sdio_get_drvdata(func);
	if (!test_and_set_bit(MWIFIEX_IFACE_WORK_DEVICE_DUMP,
			      &card->work_flags))
		schedule_work(&card->work);
}