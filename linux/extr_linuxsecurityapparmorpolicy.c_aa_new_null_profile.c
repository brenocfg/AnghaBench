#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char const* hname; int /*<<< orphan*/  profiles; } ;
struct TYPE_9__ {void* dfa; } ;
struct TYPE_8__ {void* dfa; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct aa_profile {TYPE_5__* ns; TYPE_4__ base; TYPE_3__ policy; TYPE_2__ file; int /*<<< orphan*/  parent; int /*<<< orphan*/  path_flags; TYPE_1__ label; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_11__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  level; int /*<<< orphan*/  uniq_null; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  APPARMOR_COMPLAIN ; 
 int /*<<< orphan*/  FLAG_HAT ; 
 int /*<<< orphan*/  FLAG_NULL ; 
 int /*<<< orphan*/  __add_profile (int /*<<< orphan*/ *,struct aa_profile*) ; 
 struct aa_profile* __find_child (int /*<<< orphan*/ *,char const*) ; 
 struct aa_profile* aa_alloc_profile (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct aa_profile* aa_find_child (struct aa_profile*,char const*) ; 
 int /*<<< orphan*/  aa_free_profile (struct aa_profile*) ; 
 void* aa_get_dfa (int /*<<< orphan*/ ) ; 
 TYPE_5__* aa_get_ns (TYPE_5__*) ; 
 struct aa_profile* aa_get_profile (struct aa_profile*) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nulldfa ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct aa_profile*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 
 scalar_t__ strlen (char const*) ; 

struct aa_profile *aa_new_null_profile(struct aa_profile *parent, bool hat,
				       const char *base, gfp_t gfp)
{
	struct aa_profile *p, *profile;
	const char *bname;
	char *name = NULL;

	AA_BUG(!parent);

	if (base) {
		name = kmalloc(strlen(parent->base.hname) + 8 + strlen(base),
			       gfp);
		if (name) {
			sprintf(name, "%s//null-%s", parent->base.hname, base);
			goto name;
		}
		/* fall through to try shorter uniq */
	}

	name = kmalloc(strlen(parent->base.hname) + 2 + 7 + 8, gfp);
	if (!name)
		return NULL;
	sprintf(name, "%s//null-%x", parent->base.hname,
		atomic_inc_return(&parent->ns->uniq_null));

name:
	/* lookup to see if this is a dup creation */
	bname = basename(name);
	profile = aa_find_child(parent, bname);
	if (profile)
		goto out;

	profile = aa_alloc_profile(name, NULL, gfp);
	if (!profile)
		goto fail;

	profile->mode = APPARMOR_COMPLAIN;
	profile->label.flags |= FLAG_NULL;
	if (hat)
		profile->label.flags |= FLAG_HAT;
	profile->path_flags = parent->path_flags;

	/* released on free_profile */
	rcu_assign_pointer(profile->parent, aa_get_profile(parent));
	profile->ns = aa_get_ns(parent->ns);
	profile->file.dfa = aa_get_dfa(nulldfa);
	profile->policy.dfa = aa_get_dfa(nulldfa);

	mutex_lock_nested(&profile->ns->lock, profile->ns->level);
	p = __find_child(&parent->base.profiles, bname);
	if (p) {
		aa_free_profile(profile);
		profile = aa_get_profile(p);
	} else {
		__add_profile(&parent->base.profiles, profile);
	}
	mutex_unlock(&profile->ns->lock);

	/* refcount released by caller */
out:
	kfree(name);

	return profile;

fail:
	kfree(name);
	aa_free_profile(profile);
	return NULL;
}