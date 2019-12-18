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
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct nfs_renameargs {int /*<<< orphan*/  new_dir; int /*<<< orphan*/  old_dir; struct qstr* new_name; struct qstr* old_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_diropargs (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs2_xdr_enc_renameargs(struct rpc_rqst *req,
				    struct xdr_stream *xdr,
				    const void *data)
{
	const struct nfs_renameargs *args = data;
	const struct qstr *old = args->old_name;
	const struct qstr *new = args->new_name;

	encode_diropargs(xdr, args->old_dir, old->name, old->len);
	encode_diropargs(xdr, args->new_dir, new->name, new->len);
}