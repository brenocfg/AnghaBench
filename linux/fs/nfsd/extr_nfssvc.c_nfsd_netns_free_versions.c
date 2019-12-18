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
struct nfsd_net {int /*<<< orphan*/ * nfsd4_minorversions; int /*<<< orphan*/ * nfsd_versions; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void
nfsd_netns_free_versions(struct nfsd_net *nn)
{
	kfree(nn->nfsd_versions);
	kfree(nn->nfsd4_minorversions);
	nn->nfsd_versions = NULL;
	nn->nfsd4_minorversions = NULL;
}