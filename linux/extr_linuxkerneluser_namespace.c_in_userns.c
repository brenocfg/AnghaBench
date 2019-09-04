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
struct user_namespace {scalar_t__ level; struct user_namespace* parent; } ;

/* Variables and functions */

bool in_userns(const struct user_namespace *ancestor,
	       const struct user_namespace *child)
{
	const struct user_namespace *ns;
	for (ns = child; ns->level > ancestor->level; ns = ns->parent)
		;
	return (ns == ancestor);
}