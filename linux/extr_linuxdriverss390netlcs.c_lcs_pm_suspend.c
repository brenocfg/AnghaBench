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
struct lcs_card {scalar_t__ state; int /*<<< orphan*/  gdev; scalar_t__ dev; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_DOWN ; 
 int /*<<< orphan*/  __lcs_shutdown_device (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lcs_set_allowed_threads (struct lcs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcs_wait_for_threads (struct lcs_card*,int) ; 
 int /*<<< orphan*/  netif_device_detach (scalar_t__) ; 

__attribute__((used)) static int lcs_pm_suspend(struct lcs_card *card)
{
	if (card->dev)
		netif_device_detach(card->dev);
	lcs_set_allowed_threads(card, 0);
	lcs_wait_for_threads(card, 0xffffffff);
	if (card->state != DEV_STATE_DOWN)
		__lcs_shutdown_device(card->gdev, 1);
	return 0;
}