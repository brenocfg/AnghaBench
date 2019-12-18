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
struct nci_dev {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  n_core_ops; int /*<<< orphan*/  core_ops; } ;

/* Variables and functions */
 int nci_op_ntf_packet (struct nci_dev*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nci_core_ntf_packet(struct nci_dev *ndev, __u16 opcode,
			struct sk_buff *skb)
{
	return nci_op_ntf_packet(ndev, opcode, skb, ndev->ops->core_ops,
				 ndev->ops->n_core_ops);
}