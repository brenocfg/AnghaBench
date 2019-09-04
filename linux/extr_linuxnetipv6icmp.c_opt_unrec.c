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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  _optval ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 

__attribute__((used)) static bool opt_unrec(struct sk_buff *skb, __u32 offset)
{
	u8 _optval, *op;

	offset += skb_network_offset(skb);
	op = skb_header_pointer(skb, offset, sizeof(_optval), &_optval);
	if (!op)
		return true;
	return (*op & 0xC0) == 0x80;
}