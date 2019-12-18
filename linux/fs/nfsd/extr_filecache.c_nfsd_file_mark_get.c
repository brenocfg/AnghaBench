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
struct nfsd_file_mark {int /*<<< orphan*/  nfm_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfsd_file_mark *
nfsd_file_mark_get(struct nfsd_file_mark *nfm)
{
	if (!atomic_inc_not_zero(&nfm->nfm_ref))
		return NULL;
	return nfm;
}