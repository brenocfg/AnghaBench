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
 int BT_MAX_PROTO ; 
 int /*<<< orphan*/ ** bt_proto ; 
 int /*<<< orphan*/  bt_proto_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void bt_sock_unregister(int proto)
{
	if (proto < 0 || proto >= BT_MAX_PROTO)
		return;

	write_lock(&bt_proto_lock);
	bt_proto[proto] = NULL;
	write_unlock(&bt_proto_lock);
}