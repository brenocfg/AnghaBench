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
struct TYPE_2__ {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  rwait; } ;
struct ppp {scalar_t__ n_channels; TYPE_1__ file; } ;
struct channel {int /*<<< orphan*/  clist; int /*<<< orphan*/  upl; struct ppp* ppp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppp_destroy_interface (struct ppp*) ; 
 int /*<<< orphan*/  ppp_lock (struct ppp*) ; 
 int /*<<< orphan*/  ppp_unlock (struct ppp*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ppp_disconnect_channel(struct channel *pch)
{
	struct ppp *ppp;
	int err = -EINVAL;

	write_lock_bh(&pch->upl);
	ppp = pch->ppp;
	pch->ppp = NULL;
	write_unlock_bh(&pch->upl);
	if (ppp) {
		/* remove it from the ppp unit's list */
		ppp_lock(ppp);
		list_del(&pch->clist);
		if (--ppp->n_channels == 0)
			wake_up_interruptible(&ppp->file.rwait);
		ppp_unlock(ppp);
		if (refcount_dec_and_test(&ppp->file.refcnt))
			ppp_destroy_interface(ppp);
		err = 0;
	}
	return err;
}