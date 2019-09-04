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
typedef  int /*<<< orphan*/  u_int8_t ;
struct net {int dummy; } ;

/* Variables and functions */

void xt_proto_fini(struct net *net, u_int8_t af)
{
#ifdef CONFIG_PROC_FS
	char buf[XT_FUNCTION_MAXNAMELEN];

	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_TABLES, sizeof(buf));
	remove_proc_entry(buf, net->proc_net);

	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_TARGETS, sizeof(buf));
	remove_proc_entry(buf, net->proc_net);

	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_MATCHES, sizeof(buf));
	remove_proc_entry(buf, net->proc_net);
#endif /*CONFIG_PROC_FS*/
}