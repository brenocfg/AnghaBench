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
typedef  int /*<<< orphan*/  u32 ;
struct kvec {int dummy; } ;
struct iscsi_conn {int dummy; } ;
struct iscsi_cmd {int tx_size; int /*<<< orphan*/  iov_misc_count; struct kvec* iov_misc; int /*<<< orphan*/  iov_data_count; struct kvec* iov_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int tx_data (struct iscsi_conn*,struct kvec*,int /*<<< orphan*/ ,int) ; 

int iscsit_send_tx_data(
	struct iscsi_cmd *cmd,
	struct iscsi_conn *conn,
	int use_misc)
{
	int tx_sent, tx_size;
	u32 iov_count;
	struct kvec *iov;

send_data:
	tx_size = cmd->tx_size;

	if (!use_misc) {
		iov = &cmd->iov_data[0];
		iov_count = cmd->iov_data_count;
	} else {
		iov = &cmd->iov_misc[0];
		iov_count = cmd->iov_misc_count;
	}

	tx_sent = tx_data(conn, &iov[0], iov_count, tx_size);
	if (tx_size != tx_sent) {
		if (tx_sent == -EAGAIN) {
			pr_err("tx_data() returned -EAGAIN\n");
			goto send_data;
		} else
			return -1;
	}
	cmd->tx_size = 0;

	return 0;
}