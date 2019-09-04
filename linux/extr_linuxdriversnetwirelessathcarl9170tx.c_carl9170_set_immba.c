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
struct sk_buff {scalar_t__ data; } ;
struct ar9170 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_control; } ;
struct _carl9170_tx_superframe {TYPE_1__ f; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_TX_MAC_IMM_BA ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void carl9170_set_immba(struct ar9170 *ar, struct sk_buff *skb)
{
	struct _carl9170_tx_superframe *super;

	super = (void *) skb->data;
	super->f.mac_control |= cpu_to_le16(AR9170_TX_MAC_IMM_BA);
}