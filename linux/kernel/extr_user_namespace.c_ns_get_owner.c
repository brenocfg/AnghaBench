#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct user_namespace {struct user_namespace* parent; } ;
struct ns_common {TYPE_1__* ops; } ;
struct TYPE_4__ {struct ns_common ns; } ;
struct TYPE_3__ {struct user_namespace* (* owner ) (struct ns_common*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 struct ns_common* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct user_namespace* current_user_ns () ; 
 TYPE_2__* get_user_ns (struct user_namespace*) ; 
 struct user_namespace* stub1 (struct ns_common*) ; 

struct ns_common *ns_get_owner(struct ns_common *ns)
{
	struct user_namespace *my_user_ns = current_user_ns();
	struct user_namespace *owner, *p;

	/* See if the owner is in the current user namespace */
	owner = p = ns->ops->owner(ns);
	for (;;) {
		if (!p)
			return ERR_PTR(-EPERM);
		if (p == my_user_ns)
			break;
		p = p->parent;
	}

	return &get_user_ns(owner)->ns;
}