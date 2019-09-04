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
struct genl_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GENLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 

__attribute__((used)) static int devlink_dpipe_send_and_alloc_skb(struct sk_buff **pskb,
					    struct genl_info *info)
{
	int err;

	if (*pskb) {
		err = genlmsg_reply(*pskb, info);
		if (err)
			return err;
	}
	*pskb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!*pskb)
		return -ENOMEM;
	return 0;
}