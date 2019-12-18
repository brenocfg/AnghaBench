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
struct tls_context {scalar_t__ sk_destruct; int /*<<< orphan*/  list; struct net_device* netdev; int /*<<< orphan*/  refcount; } ;
struct sock {scalar_t__ sk_destruct; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_device_list ; 
 int /*<<< orphan*/  tls_device_lock ; 
 scalar_t__ tls_device_sk_destruct ; 

__attribute__((used)) static void tls_device_attach(struct tls_context *ctx, struct sock *sk,
			      struct net_device *netdev)
{
	if (sk->sk_destruct != tls_device_sk_destruct) {
		refcount_set(&ctx->refcount, 1);
		dev_hold(netdev);
		ctx->netdev = netdev;
		spin_lock_irq(&tls_device_lock);
		list_add_tail(&ctx->list, &tls_device_list);
		spin_unlock_irq(&tls_device_lock);

		ctx->sk_destruct = sk->sk_destruct;
		sk->sk_destruct = tls_device_sk_destruct;
	}
}