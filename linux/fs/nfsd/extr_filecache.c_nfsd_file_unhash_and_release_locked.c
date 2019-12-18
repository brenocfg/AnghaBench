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
struct nfsd_file {size_t nf_hashval; int /*<<< orphan*/  nf_lru; int /*<<< orphan*/  nf_ref; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nfb_lock; } ;

/* Variables and functions */
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 TYPE_1__* nfsd_file_hashtbl ; 
 int /*<<< orphan*/  nfsd_file_unhash (struct nfsd_file*) ; 
 int /*<<< orphan*/  trace_nfsd_file_unhash_and_release_locked (struct nfsd_file*) ; 

__attribute__((used)) static bool
nfsd_file_unhash_and_release_locked(struct nfsd_file *nf, struct list_head *dispose)
{
	lockdep_assert_held(&nfsd_file_hashtbl[nf->nf_hashval].nfb_lock);

	trace_nfsd_file_unhash_and_release_locked(nf);
	if (!nfsd_file_unhash(nf))
		return false;
	/* keep final reference for nfsd_file_lru_dispose */
	if (atomic_add_unless(&nf->nf_ref, -1, 1))
		return true;

	list_add(&nf->nf_lru, dispose);
	return true;
}