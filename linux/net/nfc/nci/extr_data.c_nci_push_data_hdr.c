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
struct sk_buff {int len; } ;
struct nci_dev {int dummy; } ;
struct nci_data_hdr {int plen; scalar_t__ rfu; int /*<<< orphan*/  conn_id; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_DATA_HDR_SIZE ; 
 int /*<<< orphan*/  NCI_MT_DATA_PKT ; 
 int /*<<< orphan*/  nci_mt_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_pbf_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nci_data_hdr* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nci_push_data_hdr(struct nci_dev *ndev,
				     __u8 conn_id,
				     struct sk_buff *skb,
				     __u8 pbf)
{
	struct nci_data_hdr *hdr;
	int plen = skb->len;

	hdr = skb_push(skb, NCI_DATA_HDR_SIZE);
	hdr->conn_id = conn_id;
	hdr->rfu = 0;
	hdr->plen = plen;

	nci_mt_set((__u8 *)hdr, NCI_MT_DATA_PKT);
	nci_pbf_set((__u8 *)hdr, pbf);
}