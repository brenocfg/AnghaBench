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
struct sockaddr_can {int dummy; } ;
struct sk_buff {scalar_t__ cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  sock_skb_cb_check_size (int) ; 

__attribute__((used)) static inline unsigned int *raw_flags(struct sk_buff *skb)
{
	sock_skb_cb_check_size(sizeof(struct sockaddr_can) +
			       sizeof(unsigned int));

	/* return pointer after struct sockaddr_can */
	return (unsigned int *)(&((struct sockaddr_can *)skb->cb)[1]);
}