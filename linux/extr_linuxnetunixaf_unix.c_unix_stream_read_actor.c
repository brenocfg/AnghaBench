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
struct unix_stream_read_state {int /*<<< orphan*/  msg; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ consumed; } ;

/* Variables and functions */
 TYPE_1__ UNIXCB (struct sk_buff*) ; 
 int skb_copy_datagram_msg (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int unix_stream_read_actor(struct sk_buff *skb,
				  int skip, int chunk,
				  struct unix_stream_read_state *state)
{
	int ret;

	ret = skb_copy_datagram_msg(skb, UNIXCB(skb).consumed + skip,
				    state->msg, chunk);
	return ret ?: chunk;
}