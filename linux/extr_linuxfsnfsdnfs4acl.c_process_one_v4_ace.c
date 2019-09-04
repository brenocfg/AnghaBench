#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  deny; } ;
struct posix_acl_state {TYPE_2__* groups; TYPE_2__* users; TYPE_3__ everyone; TYPE_3__ other; TYPE_3__ group; TYPE_3__ owner; scalar_t__ empty; } ;
struct nfs4_ace {int /*<<< orphan*/  type; int /*<<< orphan*/  who_gid; int /*<<< orphan*/  who_uid; int /*<<< orphan*/  access_mask; } ;
struct TYPE_7__ {TYPE_1__* aces; } ;
struct TYPE_6__ {TYPE_3__ perms; } ;

/* Variables and functions */
#define  ACL_GROUP 132 
#define  ACL_GROUP_OBJ 131 
#define  ACL_OTHER 130 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int /*<<< orphan*/  NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE ; 
 int ace2type (struct nfs4_ace*) ; 
 int /*<<< orphan*/  allow_bits (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allow_bits_array (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deny_bits (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deny_bits_array (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int find_gid (struct posix_acl_state*,int /*<<< orphan*/ ) ; 
 int find_uid (struct posix_acl_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_one_v4_ace(struct posix_acl_state *state,
				struct nfs4_ace *ace)
{
	u32 mask = ace->access_mask;
	int i;

	state->empty = 0;

	switch (ace2type(ace)) {
	case ACL_USER_OBJ:
		if (ace->type == NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE) {
			allow_bits(&state->owner, mask);
		} else {
			deny_bits(&state->owner, mask);
		}
		break;
	case ACL_USER:
		i = find_uid(state, ace->who_uid);
		if (ace->type == NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE) {
			allow_bits(&state->users->aces[i].perms, mask);
		} else {
			deny_bits(&state->users->aces[i].perms, mask);
			mask = state->users->aces[i].perms.deny;
			deny_bits(&state->owner, mask);
		}
		break;
	case ACL_GROUP_OBJ:
		if (ace->type == NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE) {
			allow_bits(&state->group, mask);
		} else {
			deny_bits(&state->group, mask);
			mask = state->group.deny;
			deny_bits(&state->owner, mask);
			deny_bits(&state->everyone, mask);
			deny_bits_array(state->users, mask);
			deny_bits_array(state->groups, mask);
		}
		break;
	case ACL_GROUP:
		i = find_gid(state, ace->who_gid);
		if (ace->type == NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE) {
			allow_bits(&state->groups->aces[i].perms, mask);
		} else {
			deny_bits(&state->groups->aces[i].perms, mask);
			mask = state->groups->aces[i].perms.deny;
			deny_bits(&state->owner, mask);
			deny_bits(&state->group, mask);
			deny_bits(&state->everyone, mask);
			deny_bits_array(state->users, mask);
			deny_bits_array(state->groups, mask);
		}
		break;
	case ACL_OTHER:
		if (ace->type == NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE) {
			allow_bits(&state->owner, mask);
			allow_bits(&state->group, mask);
			allow_bits(&state->other, mask);
			allow_bits(&state->everyone, mask);
			allow_bits_array(state->users, mask);
			allow_bits_array(state->groups, mask);
		} else {
			deny_bits(&state->owner, mask);
			deny_bits(&state->group, mask);
			deny_bits(&state->other, mask);
			deny_bits(&state->everyone, mask);
			deny_bits_array(state->users, mask);
			deny_bits_array(state->groups, mask);
		}
	}
}