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
struct nfs4_stid {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_stateid; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ check_stateid_generation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_verify_open_stid (struct nfs4_stid*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32 nfsd4_stid_check_stateid_generation(stateid_t *in, struct nfs4_stid *s, bool has_session)
{
	__be32 ret;

	spin_lock(&s->sc_lock);
	ret = nfsd4_verify_open_stid(s);
	if (ret == nfs_ok)
		ret = check_stateid_generation(in, &s->sc_stateid, has_session);
	spin_unlock(&s->sc_lock);
	return ret;
}