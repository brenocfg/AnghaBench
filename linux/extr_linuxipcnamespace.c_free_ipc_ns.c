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
struct ipc_namespace {int /*<<< orphan*/  ns; int /*<<< orphan*/  user_ns; int /*<<< orphan*/  ucounts; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_ipc_namespaces (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipc_namespace*) ; 
 int /*<<< orphan*/  msg_exit_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  ns_free_inum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sem_exit_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  shm_exit_ns (struct ipc_namespace*) ; 

__attribute__((used)) static void free_ipc_ns(struct ipc_namespace *ns)
{
	sem_exit_ns(ns);
	msg_exit_ns(ns);
	shm_exit_ns(ns);

	dec_ipc_namespaces(ns->ucounts);
	put_user_ns(ns->user_ns);
	ns_free_inum(&ns->ns);
	kfree(ns);
}