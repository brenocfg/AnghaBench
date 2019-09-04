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
struct work_struct {int dummy; } ;
struct oom_control {int order; int /*<<< orphan*/  const gfp_mask; int /*<<< orphan*/ * memcg; int /*<<< orphan*/ * nodemask; int /*<<< orphan*/  zonelist; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  first_memory_node ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_zonelist (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  oom_lock ; 
 int /*<<< orphan*/  out_of_memory (struct oom_control*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void moom_callback(struct work_struct *ignored)
{
	const gfp_t gfp_mask = GFP_KERNEL;
	struct oom_control oc = {
		.zonelist = node_zonelist(first_memory_node, gfp_mask),
		.nodemask = NULL,
		.memcg = NULL,
		.gfp_mask = gfp_mask,
		.order = -1,
	};

	mutex_lock(&oom_lock);
	if (!out_of_memory(&oc))
		pr_info("OOM request ignored. No task eligible\n");
	mutex_unlock(&oom_lock);
}