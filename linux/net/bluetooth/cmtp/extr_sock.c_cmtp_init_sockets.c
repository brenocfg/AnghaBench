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

/* Variables and functions */
 int /*<<< orphan*/  BTPROTO_CMTP ; 
 int /*<<< orphan*/  BTPROTO_HIDP ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  BT_INFO (char*) ; 
 int bt_procfs_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bt_sock_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_sock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmtp_proto ; 
 int /*<<< orphan*/  cmtp_sk_list ; 
 int /*<<< orphan*/  cmtp_sock_family_ops ; 
 int /*<<< orphan*/  init_net ; 
 int proto_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ *) ; 

int cmtp_init_sockets(void)
{
	int err;

	err = proto_register(&cmtp_proto, 0);
	if (err < 0)
		return err;

	err = bt_sock_register(BTPROTO_CMTP, &cmtp_sock_family_ops);
	if (err < 0) {
		BT_ERR("Can't register CMTP socket");
		goto error;
	}

	err = bt_procfs_init(&init_net, "cmtp", &cmtp_sk_list, NULL);
	if (err < 0) {
		BT_ERR("Failed to create CMTP proc file");
		bt_sock_unregister(BTPROTO_HIDP);
		goto error;
	}

	BT_INFO("CMTP socket layer initialized");

	return 0;

error:
	proto_unregister(&cmtp_proto);
	return err;
}