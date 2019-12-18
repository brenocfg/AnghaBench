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
struct user_namespace {int dummy; } ;
struct nfs3_readdirres {int /*<<< orphan*/  verf; int /*<<< orphan*/  dir_attr; } ;

/* Variables and functions */
 int decode_cookieverf3 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int decode_dirlist3 (struct xdr_stream*) ; 
 int decode_post_op_attr (struct xdr_stream*,int /*<<< orphan*/ ,struct user_namespace*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int decode_readdir3resok(struct xdr_stream *xdr,
				struct nfs3_readdirres *result,
				struct user_namespace *userns)
{
	int error;

	error = decode_post_op_attr(xdr, result->dir_attr, userns);
	if (unlikely(error))
		goto out;
	/* XXX: do we need to check if result->verf != NULL ? */
	error = decode_cookieverf3(xdr, result->verf);
	if (unlikely(error))
		goto out;
	error = decode_dirlist3(xdr);
out:
	return error;
}