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
struct nfs3_linkargs {int /*<<< orphan*/  tolen; int /*<<< orphan*/  toname; int /*<<< orphan*/  tofh; int /*<<< orphan*/  fromfh; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_diropargs3 (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nfs_fh3 (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs3_xdr_enc_link3args(struct rpc_rqst *req,
				   struct xdr_stream *xdr,
				   const void *data)
{
	const struct nfs3_linkargs *args = data;

	encode_nfs_fh3(xdr, args->fromfh);
	encode_diropargs3(xdr, args->tofh, args->toname, args->tolen);
}