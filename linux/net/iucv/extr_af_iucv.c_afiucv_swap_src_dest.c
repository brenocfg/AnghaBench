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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct af_iucv_trans_hdr {char* destUserID; char* destAppName; char* srcUserID; char* srcAppName; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (char*,int) ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 struct af_iucv_trans_hdr* iucv_trans_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void afiucv_swap_src_dest(struct sk_buff *skb)
{
	struct af_iucv_trans_hdr *trans_hdr = iucv_trans_hdr(skb);
	char tmpID[8];
	char tmpName[8];

	ASCEBC(trans_hdr->destUserID, sizeof(trans_hdr->destUserID));
	ASCEBC(trans_hdr->destAppName, sizeof(trans_hdr->destAppName));
	ASCEBC(trans_hdr->srcUserID, sizeof(trans_hdr->srcUserID));
	ASCEBC(trans_hdr->srcAppName, sizeof(trans_hdr->srcAppName));
	memcpy(tmpID, trans_hdr->srcUserID, 8);
	memcpy(tmpName, trans_hdr->srcAppName, 8);
	memcpy(trans_hdr->srcUserID, trans_hdr->destUserID, 8);
	memcpy(trans_hdr->srcAppName, trans_hdr->destAppName, 8);
	memcpy(trans_hdr->destUserID, tmpID, 8);
	memcpy(trans_hdr->destAppName, tmpName, 8);
	skb_push(skb, ETH_HLEN);
	memset(skb->data, 0, ETH_HLEN);
}