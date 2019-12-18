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
struct nfsd_file {int /*<<< orphan*/  nf_rcu; scalar_t__ nf_file; scalar_t__ nf_mark; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filp_close (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (scalar_t__) ; 
 int /*<<< orphan*/  get_file (scalar_t__) ; 
 int /*<<< orphan*/  nfsd_file_mark_put (scalar_t__) ; 
 int /*<<< orphan*/  nfsd_file_slab_free ; 
 int /*<<< orphan*/  trace_nfsd_file_put_final (struct nfsd_file*) ; 

__attribute__((used)) static bool
nfsd_file_free(struct nfsd_file *nf)
{
	bool flush = false;

	trace_nfsd_file_put_final(nf);
	if (nf->nf_mark)
		nfsd_file_mark_put(nf->nf_mark);
	if (nf->nf_file) {
		get_file(nf->nf_file);
		filp_close(nf->nf_file, NULL);
		fput(nf->nf_file);
		flush = true;
	}
	call_rcu(&nf->nf_rcu, nfsd_file_slab_free);
	return flush;
}