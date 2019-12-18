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
struct posix_acl_state {int dummy; } ;
struct posix_acl {int dummy; } ;
struct nfs4_acl {int naces; struct nfs4_ace* aces; } ;
struct nfs4_ace {scalar_t__ type; int flag; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 scalar_t__ NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE ; 
 scalar_t__ NFS4_ACE_ACCESS_DENIED_ACE_TYPE ; 
 int NFS4_ACE_INHERIT_ONLY_ACE ; 
 unsigned int NFS4_ACL_DIR ; 
 unsigned int NFS4_ACL_TYPE_DEFAULT ; 
 int NFS4_INHERITANCE_FLAGS ; 
 int NFS4_SUPPORTED_FLAGS ; 
 int PTR_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  free_state (struct posix_acl_state*) ; 
 int init_state (struct posix_acl_state*,int) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 struct posix_acl* posix_state_to_acl (struct posix_acl_state*,unsigned int) ; 
 int /*<<< orphan*/  process_one_v4_ace (struct posix_acl_state*,struct nfs4_ace*) ; 
 int /*<<< orphan*/  sort_pacl (struct posix_acl*) ; 

__attribute__((used)) static int nfs4_acl_nfsv4_to_posix(struct nfs4_acl *acl,
		struct posix_acl **pacl, struct posix_acl **dpacl,
		unsigned int flags)
{
	struct posix_acl_state effective_acl_state, default_acl_state;
	struct nfs4_ace *ace;
	int ret;

	ret = init_state(&effective_acl_state, acl->naces);
	if (ret)
		return ret;
	ret = init_state(&default_acl_state, acl->naces);
	if (ret)
		goto out_estate;
	ret = -EINVAL;
	for (ace = acl->aces; ace < acl->aces + acl->naces; ace++) {
		if (ace->type != NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE &&
		    ace->type != NFS4_ACE_ACCESS_DENIED_ACE_TYPE)
			goto out_dstate;
		if (ace->flag & ~NFS4_SUPPORTED_FLAGS)
			goto out_dstate;
		if ((ace->flag & NFS4_INHERITANCE_FLAGS) == 0) {
			process_one_v4_ace(&effective_acl_state, ace);
			continue;
		}
		if (!(flags & NFS4_ACL_DIR))
			goto out_dstate;
		/*
		 * Note that when only one of FILE_INHERIT or DIRECTORY_INHERIT
		 * is set, we're effectively turning on the other.  That's OK,
		 * according to rfc 3530.
		 */
		process_one_v4_ace(&default_acl_state, ace);

		if (!(ace->flag & NFS4_ACE_INHERIT_ONLY_ACE))
			process_one_v4_ace(&effective_acl_state, ace);
	}
	*pacl = posix_state_to_acl(&effective_acl_state, flags);
	if (IS_ERR(*pacl)) {
		ret = PTR_ERR(*pacl);
		*pacl = NULL;
		goto out_dstate;
	}
	*dpacl = posix_state_to_acl(&default_acl_state,
						flags | NFS4_ACL_TYPE_DEFAULT);
	if (IS_ERR(*dpacl)) {
		ret = PTR_ERR(*dpacl);
		*dpacl = NULL;
		posix_acl_release(*pacl);
		*pacl = NULL;
		goto out_dstate;
	}
	sort_pacl(*pacl);
	sort_pacl(*dpacl);
	ret = 0;
out_dstate:
	free_state(&default_acl_state);
out_estate:
	free_state(&effective_acl_state);
	return ret;
}