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
struct chp_id {int dummy; } ;
typedef  enum cfg_task_t { ____Placeholder_cfg_task_t } cfg_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  cfg_lock ; 
 int cfg_none ; 
 int chp_cfg_fetch_task (struct chp_id*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cfg_idle(void)
{
	struct chp_id chpid;
	enum cfg_task_t t;

	spin_lock(&cfg_lock);
	t = chp_cfg_fetch_task(&chpid);
	spin_unlock(&cfg_lock);

	return t == cfg_none;
}