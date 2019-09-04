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
struct sk_buff {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void skb_debug(const struct sk_buff *skb)
{
#ifdef SKB_DEBUG
#define NUM2PRINT 50
	print_hex_dump(KERN_DEBUG, "br2684: skb: ", DUMP_OFFSET,
		       16, 1, skb->data, min(NUM2PRINT, skb->len), true);
#endif
}