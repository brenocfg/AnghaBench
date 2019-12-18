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
struct tipc_msg {int dummy; } ;
struct TYPE_2__ {int msg_lengths_total; int /*<<< orphan*/ * msg_length_profile; int /*<<< orphan*/  msg_length_counts; int /*<<< orphan*/  queue_sz_counts; int /*<<< orphan*/  accu_queue_sz; } ;
struct tipc_link {TYPE_1__ stats; int /*<<< orphan*/  transmq; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ FIRST_FRAGMENT ; 
 scalar_t__ MSG_FRAGMENTER ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 struct tipc_msg* msg_inner_hdr (struct tipc_msg*) ; 
 int msg_size (struct tipc_msg*) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void link_profile_stats(struct tipc_link *l)
{
	struct sk_buff *skb;
	struct tipc_msg *msg;
	int length;

	/* Update counters used in statistical profiling of send traffic */
	l->stats.accu_queue_sz += skb_queue_len(&l->transmq);
	l->stats.queue_sz_counts++;

	skb = skb_peek(&l->transmq);
	if (!skb)
		return;
	msg = buf_msg(skb);
	length = msg_size(msg);

	if (msg_user(msg) == MSG_FRAGMENTER) {
		if (msg_type(msg) != FIRST_FRAGMENT)
			return;
		length = msg_size(msg_inner_hdr(msg));
	}
	l->stats.msg_lengths_total += length;
	l->stats.msg_length_counts++;
	if (length <= 64)
		l->stats.msg_length_profile[0]++;
	else if (length <= 256)
		l->stats.msg_length_profile[1]++;
	else if (length <= 1024)
		l->stats.msg_length_profile[2]++;
	else if (length <= 4096)
		l->stats.msg_length_profile[3]++;
	else if (length <= 16384)
		l->stats.msg_length_profile[4]++;
	else if (length <= 32768)
		l->stats.msg_length_profile[5]++;
	else
		l->stats.msg_length_profile[6]++;
}