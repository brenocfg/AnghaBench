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
struct sk_buff {scalar_t__ destructor; scalar_t__ decrypted; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INET ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ sock_wfree ; 
 scalar_t__ tcp_wfree ; 

__attribute__((used)) static bool can_skb_orphan_partial(const struct sk_buff *skb)
{
#ifdef CONFIG_TLS_DEVICE
	/* Drivers depend on in-order delivery for crypto offload,
	 * partial orphan breaks out-of-order-OK logic.
	 */
	if (skb->decrypted)
		return false;
#endif
	return (skb->destructor == sock_wfree ||
		(IS_ENABLED(CONFIG_INET) && skb->destructor == tcp_wfree));
}