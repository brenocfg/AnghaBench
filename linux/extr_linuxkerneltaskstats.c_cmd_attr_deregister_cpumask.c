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
struct genl_info {int /*<<< orphan*/  snd_portid; int /*<<< orphan*/ * attrs; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEREGISTER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK ; 
 int add_del_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_attr_deregister_cpumask(struct genl_info *info)
{
	cpumask_var_t mask;
	int rc;

	if (!alloc_cpumask_var(&mask, GFP_KERNEL))
		return -ENOMEM;
	rc = parse(info->attrs[TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK], mask);
	if (rc < 0)
		goto out;
	rc = add_del_listener(info->snd_portid, mask, DEREGISTER);
out:
	free_cpumask_var(mask);
	return rc;
}