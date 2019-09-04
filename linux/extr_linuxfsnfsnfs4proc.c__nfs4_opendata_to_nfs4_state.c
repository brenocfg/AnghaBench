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
struct nfs4_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  seqid; int /*<<< orphan*/  fmode; } ;
struct TYPE_4__ {scalar_t__ delegation_type; int /*<<< orphan*/  stateid; } ;
struct nfs4_opendata {TYPE_1__ o_arg; TYPE_2__ o_res; int /*<<< orphan*/  state; int /*<<< orphan*/  rpc_done; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs4_state*) ; 
 int /*<<< orphan*/  nfs4_opendata_check_deleg (struct nfs4_opendata*,struct nfs4_state*) ; 
 struct nfs4_state* nfs4_opendata_find_nfs4_state (struct nfs4_opendata*) ; 
 struct nfs4_state* nfs4_try_open_cached (struct nfs4_opendata*) ; 
 int /*<<< orphan*/  nfs_release_seqid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_nfs4_cached_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_open_stateid (struct nfs4_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_state *
_nfs4_opendata_to_nfs4_state(struct nfs4_opendata *data)
{
	struct nfs4_state *state;

	if (!data->rpc_done) {
		state = nfs4_try_open_cached(data);
		trace_nfs4_cached_open(data->state);
		goto out;
	}

	state = nfs4_opendata_find_nfs4_state(data);
	if (IS_ERR(state))
		goto out;

	if (data->o_res.delegation_type != 0)
		nfs4_opendata_check_deleg(data, state);
	update_open_stateid(state, &data->o_res.stateid, NULL,
			data->o_arg.fmode);
out:
	nfs_release_seqid(data->o_arg.seqid);
	return state;
}