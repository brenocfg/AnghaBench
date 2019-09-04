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
typedef  int /*<<< orphan*/  u8 ;
struct nfc_digital_dev {scalar_t__ poll_tech_count; struct digital_poll_tech* poll_techs; } ;
struct digital_poll_tech {int /*<<< orphan*/  poll_func; int /*<<< orphan*/  rf_tech; } ;
typedef  int /*<<< orphan*/  digital_poll_t ;

/* Variables and functions */
 scalar_t__ NFC_DIGITAL_POLL_MODE_COUNT_MAX ; 

__attribute__((used)) static void digital_add_poll_tech(struct nfc_digital_dev *ddev, u8 rf_tech,
				  digital_poll_t poll_func)
{
	struct digital_poll_tech *poll_tech;

	if (ddev->poll_tech_count >= NFC_DIGITAL_POLL_MODE_COUNT_MAX)
		return;

	poll_tech = &ddev->poll_techs[ddev->poll_tech_count++];

	poll_tech->rf_tech = rf_tech;
	poll_tech->poll_func = poll_func;
}