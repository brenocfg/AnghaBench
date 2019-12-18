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
struct nfs_fsinfo {scalar_t__ lease_time; int /*<<< orphan*/  time_delta; int /*<<< orphan*/  maxfilesize; void* dtpref; void* wtmult; void* wtpref; void* wtmax; void* rtmult; void* rtpref; void* rtmax; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 void* be32_to_cpup (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdr_decode_nfstime3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_decode_size3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_fsinfo3resok(struct xdr_stream *xdr,
			       struct nfs_fsinfo *result)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, 4 * 7 + 8 + 8 + 4);
	if (unlikely(!p))
		return -EIO;
	result->rtmax  = be32_to_cpup(p++);
	result->rtpref = be32_to_cpup(p++);
	result->rtmult = be32_to_cpup(p++);
	result->wtmax  = be32_to_cpup(p++);
	result->wtpref = be32_to_cpup(p++);
	result->wtmult = be32_to_cpup(p++);
	result->dtpref = be32_to_cpup(p++);
	p = xdr_decode_size3(p, &result->maxfilesize);
	xdr_decode_nfstime3(p, &result->time_delta);

	/* ignore properties */
	result->lease_time = 0;
	return 0;
}