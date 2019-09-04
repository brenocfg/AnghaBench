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
struct rxrpc_skb_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rxrpc_to_server (struct rxrpc_skb_priv const*) ; 

__attribute__((used)) static inline bool rxrpc_to_client(const struct rxrpc_skb_priv *sp)
{
	return !rxrpc_to_server(sp);
}