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
struct nfs3_accessargs {int /*<<< orphan*/  access; int /*<<< orphan*/  fh; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_nfs_fh3 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_uint32 (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_access3args(struct xdr_stream *xdr,
			       const struct nfs3_accessargs *args)
{
	encode_nfs_fh3(xdr, args->fh);
	encode_uint32(xdr, args->access);
}