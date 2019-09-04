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

/* Variables and functions */
 int nfs4_state_start () ; 
 int nfsd_racache_init (int) ; 
 int /*<<< orphan*/  nfsd_racache_shutdown () ; 
 int /*<<< orphan*/  nfsd_users ; 

__attribute__((used)) static int nfsd_startup_generic(int nrservs)
{
	int ret;

	if (nfsd_users++)
		return 0;

	/*
	 * Readahead param cache - will no-op if it already exists.
	 * (Note therefore results will be suboptimal if number of
	 * threads is modified after nfsd start.)
	 */
	ret = nfsd_racache_init(2*nrservs);
	if (ret)
		goto dec_users;

	ret = nfs4_state_start();
	if (ret)
		goto out_racache;
	return 0;

out_racache:
	nfsd_racache_shutdown();
dec_users:
	nfsd_users--;
	return ret;
}