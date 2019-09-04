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
struct st21nfca_hci_info {int async_cb_type; int /*<<< orphan*/  async_cb_context; int /*<<< orphan*/  (* async_cb ) (int /*<<< orphan*/ ,struct sk_buff*,int) ;} ;
struct sk_buff {int /*<<< orphan*/  len; } ;

/* Variables and functions */
#define  ST21NFCA_CB_TYPE_READER_ISO15693 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*,int) ; 

__attribute__((used)) static void st21nfca_hci_data_exchange_cb(void *context, struct sk_buff *skb,
					  int err)
{
	struct st21nfca_hci_info *info = context;

	switch (info->async_cb_type) {
	case ST21NFCA_CB_TYPE_READER_ISO15693:
		if (err == 0)
			skb_trim(skb, skb->len - 1);
		info->async_cb(info->async_cb_context, skb, err);
		break;
	default:
		if (err == 0)
			kfree_skb(skb);
		break;
	}
}