#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lcs_card {scalar_t__ state; TYPE_1__* gdev; scalar_t__ dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_RECOVER ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int lcs_new_device (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_device_attach (scalar_t__) ; 

__attribute__((used)) static int lcs_pm_resume(struct lcs_card *card)
{
	int rc = 0;

	if (card->state == DEV_STATE_RECOVER)
		rc = lcs_new_device(card->gdev);
	if (card->dev)
		netif_device_attach(card->dev);
	if (rc) {
		dev_warn(&card->gdev->dev, "The lcs device driver "
			"failed to recover the device\n");
	}
	return rc;
}