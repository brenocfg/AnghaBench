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
struct svc_rqst {int dummy; } ;
struct cb_getattrargs {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  fh; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ decode_bitmap (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 scalar_t__ decode_fh (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static __be32 decode_getattr_args(struct svc_rqst *rqstp,
		struct xdr_stream *xdr, void *argp)
{
	struct cb_getattrargs *args = argp;
	__be32 status;

	status = decode_fh(xdr, &args->fh);
	if (unlikely(status != 0))
		return status;
	return decode_bitmap(xdr, args->bitmap);
}