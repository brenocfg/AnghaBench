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
struct nfsd_net {int* nfsd_versions; } ;
typedef  enum vers_op { ____Placeholder_vers_op } vers_op ;

/* Variables and functions */
#define  NFSD_AVAIL 131 
#define  NFSD_CLEAR 130 
 int NFSD_MINVERS ; 
 int NFSD_NRVERS ; 
#define  NFSD_SET 129 
#define  NFSD_TEST 128 
 int /*<<< orphan*/  nfsd_netns_init_versions (struct nfsd_net*) ; 
 int nfsd_support_version (int) ; 

int nfsd_vers(struct nfsd_net *nn, int vers, enum vers_op change)
{
	if (vers < NFSD_MINVERS || vers >= NFSD_NRVERS)
		return 0;
	switch(change) {
	case NFSD_SET:
		if (nn->nfsd_versions)
			nn->nfsd_versions[vers] = nfsd_support_version(vers);
		break;
	case NFSD_CLEAR:
		nfsd_netns_init_versions(nn);
		if (nn->nfsd_versions)
			nn->nfsd_versions[vers] = false;
		break;
	case NFSD_TEST:
		if (nn->nfsd_versions)
			return nn->nfsd_versions[vers];
		/* Fallthrough */
	case NFSD_AVAIL:
		return nfsd_support_version(vers);
	}
	return 0;
}