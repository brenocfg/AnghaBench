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
struct xdr_stream {int dummy; } ;
struct user_namespace {int dummy; } ;
struct nfs3_diropres {int /*<<< orphan*/  dir_attr; TYPE_2__* fattr; TYPE_1__* fh; } ;
struct TYPE_4__ {scalar_t__ valid; } ;
struct TYPE_3__ {scalar_t__ size; } ;

/* Variables and functions */
 int decode_post_op_attr (struct xdr_stream*,TYPE_2__*,struct user_namespace*) ; 
 int decode_post_op_fh3 (struct xdr_stream*,TYPE_1__*) ; 
 int decode_wcc_data (struct xdr_stream*,int /*<<< orphan*/ ,struct user_namespace*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int decode_create3resok(struct xdr_stream *xdr,
			       struct nfs3_diropres *result,
			       struct user_namespace *userns)
{
	int error;

	error = decode_post_op_fh3(xdr, result->fh);
	if (unlikely(error))
		goto out;
	error = decode_post_op_attr(xdr, result->fattr, userns);
	if (unlikely(error))
		goto out;
	/* The server isn't required to return a file handle.
	 * If it didn't, force the client to perform a LOOKUP
	 * to determine the correct file handle and attribute
	 * values for the new object. */
	if (result->fh->size == 0)
		result->fattr->valid = 0;
	error = decode_wcc_data(xdr, result->dir_attr, userns);
out:
	return error;
}