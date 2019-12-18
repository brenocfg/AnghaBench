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
struct linux_binprm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_clear_task_ctx_trans (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  task_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apparmor_bprm_committed_creds(struct linux_binprm *bprm)
{
	/* clear out temporary/transitional state from the context */
	aa_clear_task_ctx_trans(task_ctx(current));

	return;
}