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
struct nfs4_file {int /*<<< orphan*/  fi_lock; } ;
struct nfs4_clnt_odstate {int /*<<< orphan*/  co_client; int /*<<< orphan*/  co_perfile; int /*<<< orphan*/  co_odcount; struct nfs4_file* co_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nfs4_clnt_odstate*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_return_all_file_layouts (int /*<<< orphan*/ ,struct nfs4_file*) ; 
 int /*<<< orphan*/  odstate_slab ; 
 scalar_t__ refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
put_clnt_odstate(struct nfs4_clnt_odstate *co)
{
	struct nfs4_file *fp;

	if (!co)
		return;

	fp = co->co_file;
	if (refcount_dec_and_lock(&co->co_odcount, &fp->fi_lock)) {
		list_del(&co->co_perfile);
		spin_unlock(&fp->fi_lock);

		nfsd4_return_all_file_layouts(co->co_client, fp);
		kmem_cache_free(odstate_slab, co);
	}
}