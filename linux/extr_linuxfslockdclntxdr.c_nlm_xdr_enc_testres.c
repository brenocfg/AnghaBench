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
 int /*<<< orphan*/  encode_nlm_stat (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nlm_testrply (struct xdr_stream*,struct nlm_res const*) ; 

__attribute__((used)) static void nlm_xdr_enc_testres(struct rpc_rqst *req,
				struct xdr_stream *xdr,
				const void *data)
{
	const struct nlm_res *result = data;

	encode_cookie(xdr, &result->cookie);
	encode_nlm_stat(xdr, result->status);
	encode_nlm_testrply(xdr, result);
}