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
struct nfs4_state_owner {int dummy; } ;
struct nfs4_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs40_clear_delegation_stateid (struct nfs4_state*) ; 
 int nfs4_open_expired (struct nfs4_state_owner*,struct nfs4_state*) ; 
 int /*<<< orphan*/  nfs_state_clear_open_state_flags (struct nfs4_state*) ; 

__attribute__((used)) static int nfs40_open_expired(struct nfs4_state_owner *sp, struct nfs4_state *state)
{
	/* NFSv4.0 doesn't allow for delegation recovery on open expire */
	nfs40_clear_delegation_stateid(state);
	nfs_state_clear_open_state_flags(state);
	return nfs4_open_expired(sp, state);
}