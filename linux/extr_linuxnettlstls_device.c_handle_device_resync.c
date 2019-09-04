#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct tls_offload_context_rx {int /*<<< orphan*/  resync_req; } ;
struct tls_context {scalar_t__ rx_conf; struct net_device* netdev; } ;
struct sock {int dummy; } ;
struct net_device {TYPE_1__* tlsdev_ops; } ;
typedef  int s64 ;
struct TYPE_2__ {int /*<<< orphan*/  (* tls_dev_resync_rx ) (struct net_device*,struct sock*,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ TLS_HEADER_SIZE ; 
 scalar_t__ TLS_HW ; 
 int atomic64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic64_try_cmpxchg (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct sock*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_offload_context_rx* tls_offload_ctx_rx (struct tls_context*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

void handle_device_resync(struct sock *sk, u32 seq, u64 rcd_sn)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct net_device *netdev = tls_ctx->netdev;
	struct tls_offload_context_rx *rx_ctx;
	u32 is_req_pending;
	s64 resync_req;
	u32 req_seq;

	if (tls_ctx->rx_conf != TLS_HW)
		return;

	rx_ctx = tls_offload_ctx_rx(tls_ctx);
	resync_req = atomic64_read(&rx_ctx->resync_req);
	req_seq = ntohl(resync_req >> 32) - ((u32)TLS_HEADER_SIZE - 1);
	is_req_pending = resync_req;

	if (unlikely(is_req_pending) && req_seq == seq &&
	    atomic64_try_cmpxchg(&rx_ctx->resync_req, &resync_req, 0))
		netdev->tlsdev_ops->tls_dev_resync_rx(netdev, sk,
						      seq + TLS_HEADER_SIZE - 1,
						      rcd_sn);
}