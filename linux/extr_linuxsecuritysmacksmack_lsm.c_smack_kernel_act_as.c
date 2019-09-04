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
typedef  int /*<<< orphan*/  u32 ;
struct task_smack {int /*<<< orphan*/  smk_task; } ;
struct cred {struct task_smack* security; } ;

/* Variables and functions */
 int /*<<< orphan*/  smack_from_secid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smack_kernel_act_as(struct cred *new, u32 secid)
{
	struct task_smack *new_tsp = new->security;

	new_tsp->smk_task = smack_from_secid(secid);
	return 0;
}