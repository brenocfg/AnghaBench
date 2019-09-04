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
struct sk_buff {int /*<<< orphan*/  tc_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skbtcindex_decode(struct sk_buff *skb, void *data, u16 len)
{
	u16 ifetc_index = *(u16 *)data;

	skb->tc_index = ntohs(ifetc_index);
	return 0;
}