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
struct user_namespace {scalar_t__ level; struct user_namespace* parent; int /*<<< orphan*/  owner; } ;
struct cred {int /*<<< orphan*/  euid; struct user_namespace* user_ns; int /*<<< orphan*/  cap_effective; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ cap_raised (int /*<<< orphan*/ ,int) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cap_capable(const struct cred *cred, struct user_namespace *targ_ns,
		int cap, unsigned int opts)
{
	struct user_namespace *ns = targ_ns;

	/* See if cred has the capability in the target user namespace
	 * by examining the target user namespace and all of the target
	 * user namespace's parents.
	 */
	for (;;) {
		/* Do we have the necessary capabilities? */
		if (ns == cred->user_ns)
			return cap_raised(cred->cap_effective, cap) ? 0 : -EPERM;

		/*
		 * If we're already at a lower level than we're looking for,
		 * we're done searching.
		 */
		if (ns->level <= cred->user_ns->level)
			return -EPERM;

		/* 
		 * The owner of the user namespace in the parent of the
		 * user namespace has all caps.
		 */
		if ((ns->parent == cred->user_ns) && uid_eq(ns->owner, cred->euid))
			return 0;

		/*
		 * If you have a capability in a parent user ns, then you have
		 * it over all children user namespaces as well.
		 */
		ns = ns->parent;
	}

	/* We never get here */
}