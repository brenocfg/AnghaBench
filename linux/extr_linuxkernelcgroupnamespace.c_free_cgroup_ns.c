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
struct cgroup_namespace {int /*<<< orphan*/  ns; int /*<<< orphan*/  user_ns; int /*<<< orphan*/  ucounts; int /*<<< orphan*/  root_cset; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_cgroup_namespaces (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cgroup_namespace*) ; 
 int /*<<< orphan*/  ns_free_inum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_css_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 

void free_cgroup_ns(struct cgroup_namespace *ns)
{
	put_css_set(ns->root_cset);
	dec_cgroup_namespaces(ns->ucounts);
	put_user_ns(ns->user_ns);
	ns_free_inum(&ns->ns);
	kfree(ns);
}