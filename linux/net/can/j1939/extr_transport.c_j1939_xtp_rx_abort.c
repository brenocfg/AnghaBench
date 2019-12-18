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
struct sk_buff {int dummy; } ;
struct j1939_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  j1939_xtp_rx_abort_one (struct j1939_priv*,struct sk_buff*,int,int) ; 

__attribute__((used)) static void
j1939_xtp_rx_abort(struct j1939_priv *priv, struct sk_buff *skb,
		   bool transmitter)
{
	j1939_xtp_rx_abort_one(priv, skb, false, transmitter);
	j1939_xtp_rx_abort_one(priv, skb, true, transmitter);
}