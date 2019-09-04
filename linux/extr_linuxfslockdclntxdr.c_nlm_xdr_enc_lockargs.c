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
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int dummy; } ;
struct TYPE_2__ {scalar_t__ fl_type; } ;
struct nlm_lock {TYPE_1__ fl; } ;
struct nlm_args {int block; int reclaim; int /*<<< orphan*/  state; int /*<<< orphan*/  cookie; struct nlm_lock lock; } ;

/* Variables and functions */
 scalar_t__ F_WRLCK ; 
 int /*<<< orphan*/  encode_bool (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  encode_cookie (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_int32 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nlm_lock (struct xdr_stream*,struct nlm_lock const*) ; 

__attribute__((used)) static void nlm_xdr_enc_lockargs(struct rpc_rqst *req,
				 struct xdr_stream *xdr,
				 const void *data)
{
	const struct nlm_args *args = data;
	const struct nlm_lock *lock = &args->lock;

	encode_cookie(xdr, &args->cookie);
	encode_bool(xdr, args->block);
	encode_bool(xdr, lock->fl.fl_type == F_WRLCK);
	encode_nlm_lock(xdr, lock);
	encode_bool(xdr, args->reclaim);
	encode_int32(xdr, args->state);
}