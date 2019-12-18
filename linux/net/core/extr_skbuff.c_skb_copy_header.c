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
typedef  struct sk_buff const sk_buff ;
struct TYPE_2__ {int /*<<< orphan*/  gso_type; int /*<<< orphan*/  gso_segs; int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  __copy_skb_header (struct sk_buff const*,struct sk_buff const*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 

void skb_copy_header(struct sk_buff *new, const struct sk_buff *old)
{
	__copy_skb_header(new, old);

	skb_shinfo(new)->gso_size = skb_shinfo(old)->gso_size;
	skb_shinfo(new)->gso_segs = skb_shinfo(old)->gso_segs;
	skb_shinfo(new)->gso_type = skb_shinfo(old)->gso_type;
}