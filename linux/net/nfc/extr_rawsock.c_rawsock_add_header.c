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
typedef  scalar_t__ u8 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_HEADER_SIZE ; 
 scalar_t__ skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rawsock_add_header(struct sk_buff *skb)
{
	*(u8 *)skb_push(skb, NFC_HEADER_SIZE) = 0;

	return 0;
}