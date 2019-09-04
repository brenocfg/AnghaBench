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
struct nfs_writeverf {scalar_t__ committed; } ;
struct nfs_direct_req {int dummy; } ;
struct nfs_commit_data {int /*<<< orphan*/  verf; int /*<<< orphan*/  ds_commit_index; int /*<<< orphan*/  ds_clp; } ;

/* Variables and functions */
 int nfs_direct_cmp_verf (struct nfs_writeverf*,int /*<<< orphan*/ *) ; 
 struct nfs_writeverf* nfs_direct_select_verf (struct nfs_direct_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_direct_cmp_commit_data_verf(struct nfs_direct_req *dreq,
					   struct nfs_commit_data *data)
{
	struct nfs_writeverf *verfp;

	verfp = nfs_direct_select_verf(dreq, data->ds_clp,
					 data->ds_commit_index);

	/* verifier not set so always fail */
	if (verfp->committed < 0)
		return 1;

	return nfs_direct_cmp_verf(verfp, &data->verf);
}