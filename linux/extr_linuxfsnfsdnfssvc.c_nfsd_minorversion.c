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
typedef  enum vers_op { ____Placeholder_vers_op } vers_op ;

/* Variables and functions */
#define  NFSD_AVAIL 131 
#define  NFSD_CLEAR 130 
#define  NFSD_SET 129 
 scalar_t__ NFSD_SUPPORTED_MINOR_VERSION ; 
#define  NFSD_TEST 128 
 int /*<<< orphan*/  nfsd_adjust_nfsd_versions4 () ; 
 int* nfsd_supported_minorversions ; 
 int /*<<< orphan*/  nfsd_vers (int,int const) ; 

int nfsd_minorversion(u32 minorversion, enum vers_op change)
{
	if (minorversion > NFSD_SUPPORTED_MINOR_VERSION &&
	    change != NFSD_AVAIL)
		return -1;
	switch(change) {
	case NFSD_SET:
		nfsd_supported_minorversions[minorversion] = true;
		nfsd_vers(4, NFSD_SET);
		break;
	case NFSD_CLEAR:
		nfsd_supported_minorversions[minorversion] = false;
		nfsd_adjust_nfsd_versions4();
		break;
	case NFSD_TEST:
		return nfsd_supported_minorversions[minorversion];
	case NFSD_AVAIL:
		return minorversion <= NFSD_SUPPORTED_MINOR_VERSION;
	}
	return 0;
}