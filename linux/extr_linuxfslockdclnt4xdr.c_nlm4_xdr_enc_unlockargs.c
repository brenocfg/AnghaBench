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
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int dummy; } ;
struct nlm_lock {int dummy; } ;
struct nlm_args {int /*<<< orphan*/  cookie; struct nlm_lock lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_cookie (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_nlm4_lock (struct xdr_stream*,struct nlm_lock const*) ; 

__attribute__((used)) static void nlm4_xdr_enc_unlockargs(struct rpc_rqst *req,
				    struct xdr_stream *xdr,
				    const void *data)
{
	const struct nlm_args *args = data;
	const struct nlm_lock *lock = &args->lock;

	encode_cookie(xdr, &args->cookie);
	encode_nlm4_lock(xdr, lock);
}