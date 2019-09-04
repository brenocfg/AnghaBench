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
 int /*<<< orphan*/  bt_procfs_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bt_sock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmtp_proto ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ *) ; 

void cmtp_cleanup_sockets(void)
{
	bt_procfs_cleanup(&init_net, "cmtp");
	bt_sock_unregister(BTPROTO_CMTP);
	proto_unregister(&cmtp_proto);
}