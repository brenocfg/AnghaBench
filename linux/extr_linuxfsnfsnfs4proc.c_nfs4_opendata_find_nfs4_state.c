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
struct nfs4_state {int /*<<< orphan*/  count; struct inode* inode; } ;
struct nfs4_opendata {int /*<<< orphan*/  owner; struct nfs4_state* state; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct nfs4_state* ERR_CAST (struct inode*) ; 
 struct nfs4_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct nfs4_state* nfs4_get_open_state (struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* nfs4_opendata_get_inode (struct nfs4_opendata*) ; 

__attribute__((used)) static struct nfs4_state *
nfs4_opendata_find_nfs4_state(struct nfs4_opendata *data)
{
	struct nfs4_state *state;
	struct inode *inode;

	inode = nfs4_opendata_get_inode(data);
	if (IS_ERR(inode))
		return ERR_CAST(inode);
	if (data->state != NULL && data->state->inode == inode) {
		state = data->state;
		atomic_inc(&state->count);
	} else
		state = nfs4_get_open_state(inode, data->owner);
	iput(inode);
	if (state == NULL)
		state = ERR_PTR(-ENOMEM);
	return state;
}