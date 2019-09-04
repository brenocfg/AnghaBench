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
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MIN_H_SIZE ; 
 scalar_t__ align (int) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ msg_data (struct tipc_msg*) ; 
 int msg_data_sz (struct tipc_msg*) ; 
 int msg_size (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct tipc_msg*,int) ; 
 int skb_linearize (struct sk_buff*) ; 
 struct sk_buff* tipc_buf_acquire (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_msg_validate (struct sk_buff**) ; 
 scalar_t__ unlikely (int) ; 

bool tipc_msg_extract(struct sk_buff *skb, struct sk_buff **iskb, int *pos)
{
	struct tipc_msg *hdr, *ihdr;
	int imsz;

	*iskb = NULL;
	if (unlikely(skb_linearize(skb)))
		goto none;

	hdr = buf_msg(skb);
	if (unlikely(*pos > (msg_data_sz(hdr) - MIN_H_SIZE)))
		goto none;

	ihdr = (struct tipc_msg *)(msg_data(hdr) + *pos);
	imsz = msg_size(ihdr);

	if ((*pos + imsz) > msg_data_sz(hdr))
		goto none;

	*iskb = tipc_buf_acquire(imsz, GFP_ATOMIC);
	if (!*iskb)
		goto none;

	skb_copy_to_linear_data(*iskb, ihdr, imsz);
	if (unlikely(!tipc_msg_validate(iskb)))
		goto none;

	*pos += align(imsz);
	return true;
none:
	kfree_skb(skb);
	kfree_skb(*iskb);
	*iskb = NULL;
	return false;
}