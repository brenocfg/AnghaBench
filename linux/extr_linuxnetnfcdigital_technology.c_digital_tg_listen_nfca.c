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
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int digital_tg_config_nfca (struct nfc_digital_dev*) ; 
 int digital_tg_listen (struct nfc_digital_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  digital_tg_recv_sens_req ; 

int digital_tg_listen_nfca(struct nfc_digital_dev *ddev, u8 rf_tech)
{
	int rc;

	rc = digital_tg_config_nfca(ddev);
	if (rc)
		return rc;

	return digital_tg_listen(ddev, 300, digital_tg_recv_sens_req, NULL);
}