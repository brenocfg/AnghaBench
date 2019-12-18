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
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 unsigned long atalk_sum_skb (struct sk_buff const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static __be16 atalk_checksum(const struct sk_buff *skb, int len)
{
	unsigned long sum;

	/* skip header 4 bytes */
	sum = atalk_sum_skb(skb, 4, len-4, 0);

	/* Use 0xFFFF for 0. 0 itself means none */
	return sum ? htons((unsigned short)sum) : htons(0xFFFF);
}