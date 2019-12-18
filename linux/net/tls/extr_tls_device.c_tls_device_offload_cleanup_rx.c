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
struct tls_context {scalar_t__ tx_conf; struct net_device* netdev; } ;
struct sock {int dummy; } ;
struct net_device {TYPE_1__* tlsdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tls_dev_del ) (struct net_device*,struct tls_context*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ TLS_HW ; 
 int /*<<< orphan*/  TLS_OFFLOAD_CTX_DIR_RX ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  device_offload_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct tls_context*,int /*<<< orphan*/ ) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 int /*<<< orphan*/  tls_sw_release_resources_rx (struct sock*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void tls_device_offload_cleanup_rx(struct sock *sk)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct net_device *netdev;

	down_read(&device_offload_lock);
	netdev = tls_ctx->netdev;
	if (!netdev)
		goto out;

	netdev->tlsdev_ops->tls_dev_del(netdev, tls_ctx,
					TLS_OFFLOAD_CTX_DIR_RX);

	if (tls_ctx->tx_conf != TLS_HW) {
		dev_put(netdev);
		tls_ctx->netdev = NULL;
	}
out:
	up_read(&device_offload_lock);
	tls_sw_release_resources_rx(sk);
}