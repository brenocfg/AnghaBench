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
struct xdr_netobj {int dummy; } ;
struct nlm_share {struct nlm_share* s_next; struct nlm_host* s_host; } ;
struct nlm_host {int dummy; } ;
struct nlm_file {struct nlm_share* f_shares; } ;
struct TYPE_2__ {struct xdr_netobj oh; } ;
struct nlm_args {TYPE_1__ lock; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nlm_share*) ; 
 scalar_t__ nlm_cmp_owner (struct nlm_share*,struct xdr_netobj*) ; 
 int /*<<< orphan*/  nlm_granted ; 

__be32
nlmsvc_unshare_file(struct nlm_host *host, struct nlm_file *file,
			struct nlm_args *argp)
{
	struct nlm_share	*share, **shpp;
	struct xdr_netobj	*oh = &argp->lock.oh;

	for (shpp = &file->f_shares; (share = *shpp) != NULL;
					shpp = &share->s_next) {
		if (share->s_host == host && nlm_cmp_owner(share, oh)) {
			*shpp = share->s_next;
			kfree(share);
			return nlm_granted;
		}
	}

	/* X/Open spec says return success even if there was no
	 * corresponding share. */
	return nlm_granted;
}