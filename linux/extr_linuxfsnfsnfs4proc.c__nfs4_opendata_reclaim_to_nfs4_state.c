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
struct nfs4_state {int /*<<< orphan*/  count; struct inode* inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  fmode; } ;
struct TYPE_3__ {scalar_t__ delegation_type; int /*<<< orphan*/  stateid; } ;
struct nfs4_opendata {int rpc_status; TYPE_2__ o_arg; TYPE_1__ o_res; int /*<<< orphan*/  f_attr; int /*<<< orphan*/  rpc_done; struct nfs4_state* state; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct nfs4_state* ERR_PTR (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_opendata_check_deleg (struct nfs4_opendata*,struct nfs4_state*) ; 
 int nfs_refresh_inode (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_open_stateid (struct nfs4_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_state *
_nfs4_opendata_reclaim_to_nfs4_state(struct nfs4_opendata *data)
{
	struct inode *inode = data->state->inode;
	struct nfs4_state *state = data->state;
	int ret;

	if (!data->rpc_done) {
		if (data->rpc_status)
			return ERR_PTR(data->rpc_status);
		/* cached opens have already been processed */
		goto update;
	}

	ret = nfs_refresh_inode(inode, &data->f_attr);
	if (ret)
		return ERR_PTR(ret);

	if (data->o_res.delegation_type != 0)
		nfs4_opendata_check_deleg(data, state);
update:
	update_open_stateid(state, &data->o_res.stateid, NULL,
			    data->o_arg.fmode);
	atomic_inc(&state->count);

	return state;
}