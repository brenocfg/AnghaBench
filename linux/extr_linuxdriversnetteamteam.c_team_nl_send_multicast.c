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
struct team {int /*<<< orphan*/  dev; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  team_nl_family ; 

__attribute__((used)) static int team_nl_send_multicast(struct sk_buff *skb,
				  struct team *team, u32 portid)
{
	return genlmsg_multicast_netns(&team_nl_family, dev_net(team->dev),
				       skb, 0, 0, GFP_KERNEL);
}