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
struct nfsd_file_mark {int /*<<< orphan*/  nfm_mark; int /*<<< orphan*/  nfm_ref; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_destroy_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_put_mark (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_file_fsnotify_group ; 

__attribute__((used)) static void
nfsd_file_mark_put(struct nfsd_file_mark *nfm)
{
	if (atomic_dec_and_test(&nfm->nfm_ref)) {

		fsnotify_destroy_mark(&nfm->nfm_mark, nfsd_file_fsnotify_group);
		fsnotify_put_mark(&nfm->nfm_mark);
	}
}