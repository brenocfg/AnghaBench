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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_rp_read_version {int dummy; } ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*) ; 
 int /*<<< orphan*/  MGMT_INDEX_NONE ; 
 int /*<<< orphan*/  MGMT_OP_READ_VERSION ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_read_version*,int) ; 
 int /*<<< orphan*/  mgmt_fill_version_info (struct mgmt_rp_read_version*) ; 

__attribute__((used)) static int read_version(struct sock *sk, struct hci_dev *hdev, void *data,
			u16 data_len)
{
	struct mgmt_rp_read_version rp;

	BT_DBG("sock %p", sk);

	mgmt_fill_version_info(&rp);

	return mgmt_cmd_complete(sk, MGMT_INDEX_NONE, MGMT_OP_READ_VERSION, 0,
				 &rp, sizeof(rp));
}