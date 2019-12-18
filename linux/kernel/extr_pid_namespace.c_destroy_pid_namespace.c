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
struct pid_namespace {int /*<<< orphan*/  rcu; int /*<<< orphan*/  idr; int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayed_free_pidns ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_free_inum (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_pid_namespace(struct pid_namespace *ns)
{
	ns_free_inum(&ns->ns);

	idr_destroy(&ns->idr);
	call_rcu(&ns->rcu, delayed_free_pidns);
}