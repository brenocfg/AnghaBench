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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int nfstime4_maxsz ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdr_decode_nfstime4 (int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_attr_time(struct xdr_stream *xdr, struct timespec *time)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, nfstime4_maxsz << 2);
	if (unlikely(!p))
		return -EIO;
	xdr_decode_nfstime4(p, time);
	return 0;
}