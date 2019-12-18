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
struct nfs_diropok {int /*<<< orphan*/  fattr; int /*<<< orphan*/  fh; } ;

/* Variables and functions */
 int decode_fattr (struct xdr_stream*,int /*<<< orphan*/ ,struct user_namespace*) ; 
 int decode_fhandle (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int decode_diropok(struct xdr_stream *xdr, struct nfs_diropok *result,
		struct user_namespace *userns)
{
	int error;

	error = decode_fhandle(xdr, result->fh);
	if (unlikely(error))
		goto out;
	error = decode_fattr(xdr, result->fattr, userns);
out:
	return error;
}