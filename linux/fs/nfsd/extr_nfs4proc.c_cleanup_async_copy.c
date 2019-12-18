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
struct nfsd4_copy {TYPE_1__* cp_clp; int /*<<< orphan*/  copies; int /*<<< orphan*/  nf_src; int /*<<< orphan*/  nf_dst; } ;
struct TYPE_2__ {int /*<<< orphan*/  async_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_free_cp_state (struct nfsd4_copy*) ; 
 int /*<<< orphan*/  nfs4_put_copy (struct nfsd4_copy*) ; 
 int /*<<< orphan*/  nfsd_file_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_async_copy(struct nfsd4_copy *copy)
{
	nfs4_free_cp_state(copy);
	nfsd_file_put(copy->nf_dst);
	nfsd_file_put(copy->nf_src);
	spin_lock(&copy->cp_clp->async_lock);
	list_del(&copy->copies);
	spin_unlock(&copy->cp_clp->async_lock);
	nfs4_put_copy(copy);
}