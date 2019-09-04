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
struct nci_driver_ops {int (* rsp ) (struct nci_dev*,struct sk_buff*) ;} ;
struct nci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int ENOTSUPP ; 
 struct nci_driver_ops* ops_cmd_lookup (struct nci_driver_ops*,size_t,int /*<<< orphan*/ ) ; 
 int stub1 (struct nci_dev*,struct sk_buff*) ; 

__attribute__((used)) static int nci_op_rsp_packet(struct nci_dev *ndev, __u16 rsp_opcode,
			     struct sk_buff *skb, struct nci_driver_ops *ops,
			     size_t n_ops)
{
	struct nci_driver_ops *op;

	op = ops_cmd_lookup(ops, n_ops, rsp_opcode);
	if (!op || !op->rsp)
		return -ENOTSUPP;

	return op->rsp(ndev, skb);
}