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
struct TYPE_2__ {int /*<<< orphan*/  header; } ;
struct ctl_table_set {int (* is_seen ) (struct ctl_table_set*) ;TYPE_1__ dir; } ;
struct ctl_table_root {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_header (int /*<<< orphan*/ *,struct ctl_table_root*,struct ctl_table_set*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ctl_table_set*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  root_table ; 

void setup_sysctl_set(struct ctl_table_set *set,
	struct ctl_table_root *root,
	int (*is_seen)(struct ctl_table_set *))
{
	memset(set, 0, sizeof(*set));
	set->is_seen = is_seen;
	init_header(&set->dir.header, root, set, NULL, root_table);
}