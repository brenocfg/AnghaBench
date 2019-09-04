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
struct sk_buff {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */

__attribute__((used)) static int mtk_tag_flow_dissect(const struct sk_buff *skb, __be16 *proto,
				int *offset)
{
	*offset = 4;
	*proto = ((__be16 *)skb->data)[1];

	return 0;
}