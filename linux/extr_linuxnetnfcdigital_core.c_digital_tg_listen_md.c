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
 int /*<<< orphan*/  DIGITAL_CMD_TG_LISTEN_MD ; 
 int digital_send_cmd (struct nfc_digital_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  digital_tg_recv_md_req ; 

__attribute__((used)) static int digital_tg_listen_md(struct nfc_digital_dev *ddev, u8 rf_tech)
{
	return digital_send_cmd(ddev, DIGITAL_CMD_TG_LISTEN_MD, NULL, NULL, 500,
				digital_tg_recv_md_req, NULL);
}