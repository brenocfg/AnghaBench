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
struct net {int dummy; } ;
struct bt_sock_list {int dummy; } ;

/* Variables and functions */

int bt_procfs_init(struct net *net, const char *name,
		   struct bt_sock_list *sk_list,
		   int (* seq_show)(struct seq_file *, void *))
{
	return 0;
}