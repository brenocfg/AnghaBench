#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfsd4_compound_state {TYPE_1__* session; } ;
struct nfs4_sessionid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  se_sessionid; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (struct nfs4_sessionid*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool nfsd4_compound_in_session(struct nfsd4_compound_state *cstate, struct nfs4_sessionid *sid)
{
	if (!cstate->session)
		return false;
	return !memcmp(sid, &cstate->session->se_sessionid, sizeof(*sid));
}