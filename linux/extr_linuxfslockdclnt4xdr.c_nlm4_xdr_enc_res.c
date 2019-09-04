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
struct nlm_res {int /*<<< orphan*/  status; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_cookie (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_nlm4_stat (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nlm4_xdr_enc_res(struct rpc_rqst *req,
			     struct xdr_stream *xdr,
			     const void *data)
{
	const struct nlm_res *result = data;

	encode_cookie(xdr, &result->cookie);
	encode_nlm4_stat(xdr, result->status);
}