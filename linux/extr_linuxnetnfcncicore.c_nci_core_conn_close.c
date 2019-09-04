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
struct nci_dev {int /*<<< orphan*/  cur_conn_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_CMD_TIMEOUT ; 
 int __nci_request (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_core_conn_close_req ; 

int nci_core_conn_close(struct nci_dev *ndev, u8 conn_id)
{
	ndev->cur_conn_id = conn_id;
	return __nci_request(ndev, nci_core_conn_close_req, conn_id,
			     msecs_to_jiffies(NCI_CMD_TIMEOUT));
}