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
struct nfs4_ff_io_stat {int /*<<< orphan*/  aggregate_completion_time; int /*<<< orphan*/  total_busy_time; int /*<<< orphan*/  bytes_not_delivered; int /*<<< orphan*/  bytes_completed; int /*<<< orphan*/  ops_completed; int /*<<< orphan*/  bytes_requested; int /*<<< orphan*/  ops_requested; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ff_layout_encode_nfstime (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void
ff_layout_encode_io_latency(struct xdr_stream *xdr,
			    struct nfs4_ff_io_stat *stat)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, 5 * 8);
	p = xdr_encode_hyper(p, stat->ops_requested);
	p = xdr_encode_hyper(p, stat->bytes_requested);
	p = xdr_encode_hyper(p, stat->ops_completed);
	p = xdr_encode_hyper(p, stat->bytes_completed);
	p = xdr_encode_hyper(p, stat->bytes_not_delivered);
	ff_layout_encode_nfstime(xdr, stat->total_busy_time);
	ff_layout_encode_nfstime(xdr, stat->aggregate_completion_time);
}