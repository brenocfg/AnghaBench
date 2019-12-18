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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ pgn; int /*<<< orphan*/  dst_name; int /*<<< orphan*/  da; int /*<<< orphan*/  src_name; int /*<<< orphan*/  sa; } ;
struct j1939_sk_buff_cb {TYPE_1__ addr; } ;
struct j1939_priv {int dummy; } ;
struct j1939_ecu {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ J1939_PGN_ADDRESS_CLAIMED ; 
 int /*<<< orphan*/  j1939_ac_process (struct j1939_priv*,struct sk_buff*) ; 
 scalar_t__ j1939_address_is_unicast (int /*<<< orphan*/ ) ; 
 struct j1939_ecu* j1939_ecu_get_by_addr (struct j1939_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_ecu_put (struct j1939_ecu*) ; 
 struct j1939_sk_buff_cb* j1939_skb_to_cb (struct sk_buff*) ; 

void j1939_ac_recv(struct j1939_priv *priv, struct sk_buff *skb)
{
	struct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	struct j1939_ecu *ecu;

	/* network mgmt */
	if (skcb->addr.pgn == J1939_PGN_ADDRESS_CLAIMED) {
		j1939_ac_process(priv, skb);
	} else if (j1939_address_is_unicast(skcb->addr.sa)) {
		/* assign source name */
		ecu = j1939_ecu_get_by_addr(priv, skcb->addr.sa);
		if (ecu) {
			skcb->addr.src_name = ecu->name;
			j1939_ecu_put(ecu);
		}
	}

	/* assign destination name */
	ecu = j1939_ecu_get_by_addr(priv, skcb->addr.da);
	if (ecu) {
		skcb->addr.dst_name = ecu->name;
		j1939_ecu_put(ecu);
	}
}