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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tls_context {int /*<<< orphan*/  flags; int /*<<< orphan*/  netdev; } ;
struct sock {int dummy; } ;
struct net_device {TYPE_1__* tlsdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tls_dev_resync ) (struct net_device*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct net_device* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS_OFFLOAD_CTX_DIR_RX ; 
 int /*<<< orphan*/  TLS_RX_SYNC_RUNNING ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tls_device_resync_rx(struct tls_context *tls_ctx,
				 struct sock *sk, u32 seq, u8 *rcd_sn)
{
	struct net_device *netdev;

	if (WARN_ON(test_and_set_bit(TLS_RX_SYNC_RUNNING, &tls_ctx->flags)))
		return;
	netdev = READ_ONCE(tls_ctx->netdev);
	if (netdev)
		netdev->tlsdev_ops->tls_dev_resync(netdev, sk, seq, rcd_sn,
						   TLS_OFFLOAD_CTX_DIR_RX);
	clear_bit_unlock(TLS_RX_SYNC_RUNNING, &tls_ctx->flags);
}