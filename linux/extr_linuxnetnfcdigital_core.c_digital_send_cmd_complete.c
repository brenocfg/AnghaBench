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
struct sk_buff {int dummy; } ;
struct nfc_digital_dev {int /*<<< orphan*/  cmd_complete_work; } ;
struct digital_cmd {struct sk_buff* resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void digital_send_cmd_complete(struct nfc_digital_dev *ddev,
				      void *arg, struct sk_buff *resp)
{
	struct digital_cmd *cmd = arg;

	cmd->resp = resp;

	schedule_work(&ddev->cmd_complete_work);
}