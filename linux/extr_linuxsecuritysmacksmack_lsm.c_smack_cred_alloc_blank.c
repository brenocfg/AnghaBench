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
struct task_smack {int dummy; } ;
struct cred {struct task_smack* security; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct task_smack* new_task_smack (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smack_cred_alloc_blank(struct cred *cred, gfp_t gfp)
{
	struct task_smack *tsp;

	tsp = new_task_smack(NULL, NULL, gfp);
	if (tsp == NULL)
		return -ENOMEM;

	cred->security = tsp;

	return 0;
}