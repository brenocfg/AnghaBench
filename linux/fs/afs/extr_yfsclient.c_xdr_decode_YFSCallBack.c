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
struct yfs_xdr_YFSCallBack {int /*<<< orphan*/  expiration_time; } ;
struct afs_callback {int /*<<< orphan*/  expires_at; } ;
struct afs_status_cb {int have_cb; struct afs_callback callback; } ;
struct afs_call {int /*<<< orphan*/  reply_time; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_divns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_size (struct yfs_xdr_YFSCallBack*) ; 
 int xdr_to_u64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xdr_decode_YFSCallBack(const __be32 **_bp,
				   struct afs_call *call,
				   struct afs_status_cb *scb)
{
	struct yfs_xdr_YFSCallBack *x = (void *)*_bp;
	struct afs_callback *cb = &scb->callback;
	ktime_t cb_expiry;

	cb_expiry = call->reply_time;
	cb_expiry = ktime_add(cb_expiry, xdr_to_u64(x->expiration_time) * 100);
	cb->expires_at	= ktime_divns(cb_expiry, NSEC_PER_SEC);
	scb->have_cb	= true;
	*_bp += xdr_size(x);
}