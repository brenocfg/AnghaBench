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
struct ctl_table_header {int dummy; } ;
struct ctl_table {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_set; } ;

/* Variables and functions */
 struct ctl_table_header* __register_sysctl_table (int /*<<< orphan*/ *,char const*,struct ctl_table*) ; 
 TYPE_1__ sysctl_table_root ; 

struct ctl_table_header *register_sysctl(const char *path, struct ctl_table *table)
{
	return __register_sysctl_table(&sysctl_table_root.default_set,
					path, table);
}