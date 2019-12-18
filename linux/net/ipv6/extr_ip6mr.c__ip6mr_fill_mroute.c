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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct mr_table {int dummy; } ;
struct mr_mfc {int dummy; } ;
struct mfc6_cache {int dummy; } ;

/* Variables and functions */
 int ip6mr_fill_mroute (struct mr_table*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mfc6_cache*,int,int) ; 

__attribute__((used)) static int _ip6mr_fill_mroute(struct mr_table *mrt, struct sk_buff *skb,
			      u32 portid, u32 seq, struct mr_mfc *c,
			      int cmd, int flags)
{
	return ip6mr_fill_mroute(mrt, skb, portid, seq, (struct mfc6_cache *)c,
				 cmd, flags);
}