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
struct net {int /*<<< orphan*/  sysctls; } ;
struct ctl_table_header {int dummy; } ;
struct ctl_table {int dummy; } ;

/* Variables and functions */
 struct ctl_table_header* __register_sysctl_table (int /*<<< orphan*/ *,char const*,struct ctl_table*) ; 

struct ctl_table_header *register_net_sysctl(struct net *net,
	const char *path, struct ctl_table *table)
{
	return __register_sysctl_table(&net->sysctls, path, table);
}