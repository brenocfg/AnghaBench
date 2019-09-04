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
struct TYPE_4__ {int /*<<< orphan*/  seq_res; } ;
struct TYPE_3__ {scalar_t__ claim; } ;
struct nfs4_opendata {TYPE_2__ o_res; TYPE_1__ o_arg; } ;

/* Variables and functions */
 scalar_t__ NFS4_OPEN_CLAIM_PREVIOUS ; 
 struct nfs4_state* _nfs4_opendata_reclaim_to_nfs4_state (struct nfs4_opendata*) ; 
 struct nfs4_state* _nfs4_opendata_to_nfs4_state (struct nfs4_opendata*) ; 
 int /*<<< orphan*/  nfs4_sequence_free_slot (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_state *
nfs4_opendata_to_nfs4_state(struct nfs4_opendata *data)
{
	struct nfs4_state *ret;

	if (data->o_arg.claim == NFS4_OPEN_CLAIM_PREVIOUS)
		ret =_nfs4_opendata_reclaim_to_nfs4_state(data);
	else
		ret = _nfs4_opendata_to_nfs4_state(data);
	nfs4_sequence_free_slot(&data->o_res.seq_res);
	return ret;
}