#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct xdr_buf {scalar_t__ len; scalar_t__ buflen; } ;
struct nfsd4_slot {int sl_flags; } ;
struct TYPE_4__ {struct nfsd4_slot* slot; } ;
struct nfsd4_compoundres {TYPE_2__ cstate; TYPE_1__* rqstp; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {struct xdr_buf rq_res; } ;

/* Variables and functions */
 int NFSD4_SLOT_CACHETHIS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd4_has_session (TYPE_2__*) ; 
 int /*<<< orphan*/  nfserr_rep_too_big ; 
 int /*<<< orphan*/  nfserr_rep_too_big_to_cache ; 
 int /*<<< orphan*/  nfserr_resource ; 

__be32 nfsd4_check_resp_size(struct nfsd4_compoundres *resp, u32 respsize)
{
	struct xdr_buf *buf = &resp->rqstp->rq_res;
	struct nfsd4_slot *slot = resp->cstate.slot;

	if (buf->len + respsize <= buf->buflen)
		return nfs_ok;
	if (!nfsd4_has_session(&resp->cstate))
		return nfserr_resource;
	if (slot->sl_flags & NFSD4_SLOT_CACHETHIS) {
		WARN_ON_ONCE(1);
		return nfserr_rep_too_big_to_cache;
	}
	return nfserr_rep_too_big;
}