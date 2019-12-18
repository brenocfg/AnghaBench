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
typedef  int /*<<< orphan*/  u8 ;
struct nci_dev {TYPE_1__* hci_dev; } ;
struct nci_data {scalar_t__ data_len; int /*<<< orphan*/ * data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  pipe; int /*<<< orphan*/  conn_id; } ;
struct nci_conn_info {int /*<<< orphan*/  conn_id; } ;
struct TYPE_2__ {struct nci_conn_info* conn_info; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  NCI_DATA_TIMEOUT ; 
 int /*<<< orphan*/  NCI_HCI_ANY_OPEN_PIPE ; 
 int /*<<< orphan*/  NCI_HCI_HCP_COMMAND ; 
 int /*<<< orphan*/  NCI_HCP_HEADER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_hci_send_data_req ; 
 int nci_request (struct nci_dev*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

int nci_hci_open_pipe(struct nci_dev *ndev, u8 pipe)
{
	struct nci_data data;
	struct nci_conn_info    *conn_info;

	conn_info = ndev->hci_dev->conn_info;
	if (!conn_info)
		return -EPROTO;

	data.conn_id = conn_info->conn_id;
	data.pipe = pipe;
	data.cmd = NCI_HCP_HEADER(NCI_HCI_HCP_COMMAND,
				       NCI_HCI_ANY_OPEN_PIPE);
	data.data = NULL;
	data.data_len = 0;

	return nci_request(ndev, nci_hci_send_data_req,
			(unsigned long)&data,
			msecs_to_jiffies(NCI_DATA_TIMEOUT));
}