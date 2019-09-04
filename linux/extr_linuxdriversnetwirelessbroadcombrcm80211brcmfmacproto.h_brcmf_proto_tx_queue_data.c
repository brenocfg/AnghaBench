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
struct brcmf_pub {TYPE_1__* proto; } ;
struct TYPE_2__ {int (* tx_queue_data ) (struct brcmf_pub*,int,struct sk_buff*) ;} ;

/* Variables and functions */
 int stub1 (struct brcmf_pub*,int,struct sk_buff*) ; 

__attribute__((used)) static inline int brcmf_proto_tx_queue_data(struct brcmf_pub *drvr, int ifidx,
					    struct sk_buff *skb)
{
	return drvr->proto->tx_queue_data(drvr, ifidx, skb);
}