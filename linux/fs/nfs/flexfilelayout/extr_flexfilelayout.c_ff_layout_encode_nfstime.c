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
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct timespec64 ktime_to_timespec64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void
ff_layout_encode_nfstime(struct xdr_stream *xdr,
			 ktime_t t)
{
	struct timespec64 ts;
	__be32 *p;

	p = xdr_reserve_space(xdr, 12);
	ts = ktime_to_timespec64(t);
	p = xdr_encode_hyper(p, ts.tv_sec);
	*p++ = cpu_to_be32(ts.tv_nsec);
}