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
struct nfc_target {int dummy; } ;
struct nfc_digital_dev {scalar_t__ curr_protocol; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  digital_abort_cmd (struct nfc_digital_dev*) ; 
 struct nfc_digital_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void digital_deactivate_target(struct nfc_dev *nfc_dev,
				      struct nfc_target *target,
				      u8 mode)
{
	struct nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);

	if (!ddev->curr_protocol) {
		pr_err("No active target\n");
		return;
	}

	digital_abort_cmd(ddev);
	ddev->curr_protocol = 0;
}