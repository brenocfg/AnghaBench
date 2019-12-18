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
struct cmtp_session {struct sk_buff** reassembly; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct cmtp_session*,unsigned char const*,int) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,unsigned char const*,int) ; 

__attribute__((used)) static inline void cmtp_add_msgpart(struct cmtp_session *session, int id, const unsigned char *buf, int count)
{
	struct sk_buff *skb = session->reassembly[id], *nskb;
	int size;

	BT_DBG("session %p buf %p count %d", session, buf, count);

	size = (skb) ? skb->len + count : count;

	nskb = alloc_skb(size, GFP_ATOMIC);
	if (!nskb) {
		BT_ERR("Can't allocate memory for CAPI message");
		return;
	}

	if (skb && (skb->len > 0))
		skb_copy_from_linear_data(skb, skb_put(nskb, skb->len), skb->len);

	skb_put_data(nskb, buf, count);

	session->reassembly[id] = nskb;

	kfree_skb(skb);
}