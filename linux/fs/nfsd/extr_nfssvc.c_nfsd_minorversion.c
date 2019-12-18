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
typedef  scalar_t__ u32 ;
struct nfsd_net {int* nfsd4_minorversions; } ;
typedef  enum vers_op { ____Placeholder_vers_op } vers_op ;

/* Variables and functions */
#define  NFSD_AVAIL 131 
#define  NFSD_CLEAR 130 
#define  NFSD_SET 129 
 scalar_t__ NFSD_SUPPORTED_MINOR_VERSION ; 
#define  NFSD_TEST 128 
 int /*<<< orphan*/  nfsd_adjust_nfsd_versions4 (struct nfsd_net*) ; 
 int /*<<< orphan*/  nfsd_netns_init_versions (struct nfsd_net*) ; 
 int nfsd_vers (struct nfsd_net*,int,int const) ; 

int nfsd_minorversion(struct nfsd_net *nn, u32 minorversion, enum vers_op change)
{
	if (minorversion > NFSD_SUPPORTED_MINOR_VERSION &&
	    change != NFSD_AVAIL)
		return -1;

	switch(change) {
	case NFSD_SET:
		if (nn->nfsd4_minorversions) {
			nfsd_vers(nn, 4, NFSD_SET);
			nn->nfsd4_minorversions[minorversion] =
				nfsd_vers(nn, 4, NFSD_TEST);
		}
		break;
	case NFSD_CLEAR:
		nfsd_netns_init_versions(nn);
		if (nn->nfsd4_minorversions) {
			nn->nfsd4_minorversions[minorversion] = false;
			nfsd_adjust_nfsd_versions4(nn);
		}
		break;
	case NFSD_TEST:
		if (nn->nfsd4_minorversions)
			return nn->nfsd4_minorversions[minorversion];
		return nfsd_vers(nn, 4, NFSD_TEST);
	case NFSD_AVAIL:
		return minorversion <= NFSD_SUPPORTED_MINOR_VERSION &&
			nfsd_vers(nn, 4, NFSD_AVAIL);
	}
	return 0;
}