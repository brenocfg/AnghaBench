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
struct list_head {int dummy; } ;
struct linux_binprm {int dummy; } ;
struct aa_label {int dummy; } ;
struct aa_profile {struct aa_label label; } ;
struct aa_ns {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __attach_match (struct linux_binprm const*,char const*,struct list_head*,char const**) ; 
 struct aa_profile* aa_get_profile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct aa_label *find_attach(const struct linux_binprm *bprm,
				    struct aa_ns *ns, struct list_head *list,
				    const char *name, const char **info)
{
	struct aa_profile *profile;

	rcu_read_lock();
	profile = aa_get_profile(__attach_match(bprm, name, list, info));
	rcu_read_unlock();

	return profile ? &profile->label : NULL;
}