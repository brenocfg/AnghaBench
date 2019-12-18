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
struct uts_namespace {int dummy; } ;
struct user_namespace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long CLONE_NEWUTS ; 
 struct uts_namespace* clone_uts_ns (struct user_namespace*,struct uts_namespace*) ; 
 int /*<<< orphan*/  get_uts_ns (struct uts_namespace*) ; 
 int /*<<< orphan*/  put_uts_ns (struct uts_namespace*) ; 

struct uts_namespace *copy_utsname(unsigned long flags,
	struct user_namespace *user_ns, struct uts_namespace *old_ns)
{
	struct uts_namespace *new_ns;

	BUG_ON(!old_ns);
	get_uts_ns(old_ns);

	if (!(flags & CLONE_NEWUTS))
		return old_ns;

	new_ns = clone_uts_ns(user_ns, old_ns);

	put_uts_ns(old_ns);
	return new_ns;
}