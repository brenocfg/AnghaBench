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
struct afs_callback {int /*<<< orphan*/  expires_at; } ;
struct afs_status_cb {int have_cb; struct afs_callback callback; } ;
struct afs_call {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_decode_expiry (struct afs_call*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xdr_decode_AFSCallBack(const __be32 **_bp,
				   struct afs_call *call,
				   struct afs_status_cb *scb)
{
	struct afs_callback *cb = &scb->callback;
	const __be32 *bp = *_bp;

	bp++; /* version */
	cb->expires_at	= xdr_decode_expiry(call, ntohl(*bp++));
	bp++; /* type */
	scb->have_cb	= true;
	*_bp = bp;
}