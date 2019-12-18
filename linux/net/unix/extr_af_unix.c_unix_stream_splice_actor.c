#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct unix_stream_read_state {int /*<<< orphan*/  splice_flags; int /*<<< orphan*/  pipe; TYPE_1__* socket; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ consumed; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 TYPE_2__ UNIXCB (struct sk_buff*) ; 
 int skb_splice_bits (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unix_stream_splice_actor(struct sk_buff *skb,
				    int skip, int chunk,
				    struct unix_stream_read_state *state)
{
	return skb_splice_bits(skb, state->socket->sk,
			       UNIXCB(skb).consumed + skip,
			       state->pipe, chunk, state->splice_flags);
}