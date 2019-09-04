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
struct nfc_digital_dev {scalar_t__ curr_protocol; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  digital_abort_cmd (struct nfc_digital_dev*) ; 
 struct nfc_digital_dev* nfc_get_drvdata (struct nfc_dev*) ; 

__attribute__((used)) static int digital_dep_link_down(struct nfc_dev *nfc_dev)
{
	struct nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);

	digital_abort_cmd(ddev);

	ddev->curr_protocol = 0;

	return 0;
}