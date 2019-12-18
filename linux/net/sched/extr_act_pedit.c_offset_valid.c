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

/* Variables and functions */
 int skb_headroom (struct sk_buff*) ; 

__attribute__((used)) static bool offset_valid(struct sk_buff *skb, int offset)
{
	if (offset > 0 && offset > skb->len)
		return false;

	if  (offset < 0 && -offset > skb_headroom(skb))
		return false;

	return true;
}