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
struct TYPE_4__ {char* hname; } ;
struct aa_profile {TYPE_2__ base; } ;
struct aa_ns {int /*<<< orphan*/  lock; int /*<<< orphan*/  base; int /*<<< orphan*/  level; TYPE_1__* parent; } ;
struct aa_label {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t ENOENT ; 
 int /*<<< orphan*/  OP_PROF_RM ; 
 int /*<<< orphan*/  __aa_bump_ns_revision (struct aa_ns*) ; 
 int /*<<< orphan*/  __aa_labelset_update_subtree (struct aa_ns*) ; 
 int /*<<< orphan*/  __aa_remove_ns (struct aa_ns*) ; 
 int /*<<< orphan*/  __lookup_profile (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  __remove_profile (struct aa_profile*) ; 
 struct aa_ns* aa_get_ns (struct aa_ns*) ; 
 struct aa_profile* aa_get_profile (int /*<<< orphan*/ ) ; 
 struct aa_ns* aa_lookupn_ns (struct aa_ns*,char const*,size_t) ; 
 int /*<<< orphan*/  aa_put_ns (struct aa_ns*) ; 
 int /*<<< orphan*/  aa_put_profile (struct aa_profile*) ; 
 char* aa_splitn_fqname (char*,size_t,char const**,size_t*) ; 
 int /*<<< orphan*/  audit_policy (struct aa_label*,int /*<<< orphan*/ ,char const*,char const*,char const*,size_t) ; 
 struct aa_ns* labels_ns (struct aa_label*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

ssize_t aa_remove_profiles(struct aa_ns *policy_ns, struct aa_label *subj,
			   char *fqname, size_t size)
{
	struct aa_ns *ns = NULL;
	struct aa_profile *profile = NULL;
	const char *name = fqname, *info = NULL;
	const char *ns_name = NULL;
	ssize_t error = 0;

	if (*fqname == 0) {
		info = "no profile specified";
		error = -ENOENT;
		goto fail;
	}

	if (fqname[0] == ':') {
		size_t ns_len;

		name = aa_splitn_fqname(fqname, size, &ns_name, &ns_len);
		/* released below */
		ns = aa_lookupn_ns(policy_ns ? policy_ns : labels_ns(subj),
				   ns_name, ns_len);
		if (!ns) {
			info = "namespace does not exist";
			error = -ENOENT;
			goto fail;
		}
	} else
		/* released below */
		ns = aa_get_ns(policy_ns ? policy_ns : labels_ns(subj));

	if (!name) {
		/* remove namespace - can only happen if fqname[0] == ':' */
		mutex_lock_nested(&ns->parent->lock, ns->level);
		__aa_remove_ns(ns);
		__aa_bump_ns_revision(ns);
		mutex_unlock(&ns->parent->lock);
	} else {
		/* remove profile */
		mutex_lock_nested(&ns->lock, ns->level);
		profile = aa_get_profile(__lookup_profile(&ns->base, name));
		if (!profile) {
			error = -ENOENT;
			info = "profile does not exist";
			goto fail_ns_lock;
		}
		name = profile->base.hname;
		__remove_profile(profile);
		__aa_labelset_update_subtree(ns);
		__aa_bump_ns_revision(ns);
		mutex_unlock(&ns->lock);
	}

	/* don't fail removal if audit fails */
	(void) audit_policy(subj, OP_PROF_RM, ns_name, name, info,
			    error);
	aa_put_ns(ns);
	aa_put_profile(profile);
	return size;

fail_ns_lock:
	mutex_unlock(&ns->lock);
	aa_put_ns(ns);

fail:
	(void) audit_policy(subj, OP_PROF_RM, ns_name, name, info,
			    error);
	return error;
}