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
struct nfs_open_context {int /*<<< orphan*/  dentry; } ;
struct nfs4_state {struct inode* inode; } ;
struct nfs4_label {int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;

/* Variables and functions */
 struct inode* ERR_CAST (struct nfs4_state*) ; 
 scalar_t__ IS_ERR (struct nfs4_state*) ; 
 struct nfs4_state* nfs4_do_open (struct inode*,struct nfs_open_context*,int,struct iattr*,struct nfs4_label*,int*) ; 
 struct nfs4_label* nfs4_label_init_security (struct inode*,int /*<<< orphan*/ ,struct iattr*,struct nfs4_label*) ; 
 int /*<<< orphan*/  nfs4_label_release_security (struct nfs4_label*) ; 

__attribute__((used)) static struct inode *
nfs4_atomic_open(struct inode *dir, struct nfs_open_context *ctx,
		int open_flags, struct iattr *attr, int *opened)
{
	struct nfs4_state *state;
	struct nfs4_label l = {0, 0, 0, NULL}, *label = NULL;

	label = nfs4_label_init_security(dir, ctx->dentry, attr, &l);

	/* Protect against concurrent sillydeletes */
	state = nfs4_do_open(dir, ctx, open_flags, attr, label, opened);

	nfs4_label_release_security(label);

	if (IS_ERR(state))
		return ERR_CAST(state);
	return state->inode;
}