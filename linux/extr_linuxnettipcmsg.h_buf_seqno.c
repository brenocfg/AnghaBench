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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_seqno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 buf_seqno(struct sk_buff *skb)
{
	return msg_seqno(buf_msg(skb));
}