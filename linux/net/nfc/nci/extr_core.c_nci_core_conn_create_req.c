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
struct nci_dev {int dummy; } ;
struct core_conn_create_data {int /*<<< orphan*/  cmd; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_OP_CORE_CONN_CREATE_CMD ; 
 int /*<<< orphan*/  nci_send_cmd (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nci_core_conn_create_req(struct nci_dev *ndev, unsigned long opt)
{
	struct core_conn_create_data *data =
					(struct core_conn_create_data *)opt;

	nci_send_cmd(ndev, NCI_OP_CORE_CONN_CREATE_CMD, data->length, data->cmd);
}