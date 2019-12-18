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
struct nfsd_net {scalar_t__* nfsd4_minorversions; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_CLEAR ; 
 unsigned int NFSD_SUPPORTED_MINOR_VERSION ; 
 int /*<<< orphan*/  nfsd_vers (struct nfsd_net*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfsd_adjust_nfsd_versions4(struct nfsd_net *nn)
{
	unsigned i;

	for (i = 0; i <= NFSD_SUPPORTED_MINOR_VERSION; i++) {
		if (nn->nfsd4_minorversions[i])
			return;
	}
	nfsd_vers(nn, 4, NFSD_CLEAR);
}