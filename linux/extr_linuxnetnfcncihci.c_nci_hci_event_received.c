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
struct sk_buff {int dummy; } ;
struct nci_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hci_event_received ) (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void nci_hci_event_received(struct nci_dev *ndev, u8 pipe,
				   u8 event, struct sk_buff *skb)
{
	if (ndev->ops->hci_event_received)
		ndev->ops->hci_event_received(ndev, pipe, event, skb);
}