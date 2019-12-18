#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  allow; } ;
struct TYPE_14__ {int /*<<< orphan*/  allow; } ;
struct TYPE_16__ {int /*<<< orphan*/  allow; } ;
struct TYPE_9__ {int /*<<< orphan*/  allow; } ;
struct posix_acl_state {TYPE_7__ other; TYPE_6__ mask; TYPE_5__* groups; TYPE_4__* users; TYPE_8__ group; TYPE_1__ owner; scalar_t__ empty; } ;
struct posix_acl_entry {int /*<<< orphan*/  e_perm; int /*<<< orphan*/  e_tag; int /*<<< orphan*/  e_gid; int /*<<< orphan*/  e_uid; } ;
struct posix_acl {struct posix_acl_entry* a_entries; } ;
struct TYPE_13__ {int n; TYPE_3__* aces; } ;
struct TYPE_12__ {int n; TYPE_2__* aces; } ;
struct TYPE_11__ {TYPE_8__ perms; int /*<<< orphan*/  gid; } ;
struct TYPE_10__ {TYPE_8__ perms; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_GROUP ; 
 int /*<<< orphan*/  ACL_GROUP_OBJ ; 
 int /*<<< orphan*/  ACL_MASK ; 
 int /*<<< orphan*/  ACL_OTHER ; 
 int /*<<< orphan*/  ACL_USER ; 
 int /*<<< orphan*/  ACL_USER_OBJ ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct posix_acl* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int NFS4_ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  add_to_mask (struct posix_acl_state*,TYPE_8__*) ; 
 int /*<<< orphan*/  low_mode_from_nfs4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 struct posix_acl* posix_acl_alloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct posix_acl *
posix_state_to_acl(struct posix_acl_state *state, unsigned int flags)
{
	struct posix_acl_entry *pace;
	struct posix_acl *pacl;
	int nace;
	int i;

	/*
	 * ACLs with no ACEs are treated differently in the inheritable
	 * and effective cases: when there are no inheritable ACEs,
	 * calls ->set_acl with a NULL ACL structure.
	 */
	if (state->empty && (flags & NFS4_ACL_TYPE_DEFAULT))
		return NULL;

	/*
	 * When there are no effective ACEs, the following will end
	 * up setting a 3-element effective posix ACL with all
	 * permissions zero.
	 */
	if (!state->users->n && !state->groups->n)
		nace = 3;
	else /* Note we also include a MASK ACE in this case: */
		nace = 4 + state->users->n + state->groups->n;
	pacl = posix_acl_alloc(nace, GFP_KERNEL);
	if (!pacl)
		return ERR_PTR(-ENOMEM);

	pace = pacl->a_entries;
	pace->e_tag = ACL_USER_OBJ;
	low_mode_from_nfs4(state->owner.allow, &pace->e_perm, flags);

	for (i=0; i < state->users->n; i++) {
		pace++;
		pace->e_tag = ACL_USER;
		low_mode_from_nfs4(state->users->aces[i].perms.allow,
					&pace->e_perm, flags);
		pace->e_uid = state->users->aces[i].uid;
		add_to_mask(state, &state->users->aces[i].perms);
	}

	pace++;
	pace->e_tag = ACL_GROUP_OBJ;
	low_mode_from_nfs4(state->group.allow, &pace->e_perm, flags);
	add_to_mask(state, &state->group);

	for (i=0; i < state->groups->n; i++) {
		pace++;
		pace->e_tag = ACL_GROUP;
		low_mode_from_nfs4(state->groups->aces[i].perms.allow,
					&pace->e_perm, flags);
		pace->e_gid = state->groups->aces[i].gid;
		add_to_mask(state, &state->groups->aces[i].perms);
	}

	if (state->users->n || state->groups->n) {
		pace++;
		pace->e_tag = ACL_MASK;
		low_mode_from_nfs4(state->mask.allow, &pace->e_perm, flags);
	}

	pace++;
	pace->e_tag = ACL_OTHER;
	low_mode_from_nfs4(state->other.allow, &pace->e_perm, flags);

	return pacl;
}