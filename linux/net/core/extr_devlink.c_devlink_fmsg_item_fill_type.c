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
struct devlink_fmsg_item {int nla_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_FMSG_OBJ_VALUE_TYPE ; 
 int EINVAL ; 
#define  NLA_BINARY 133 
#define  NLA_FLAG 132 
#define  NLA_NUL_STRING 131 
#define  NLA_U32 130 
#define  NLA_U64 129 
#define  NLA_U8 128 
 int nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
devlink_fmsg_item_fill_type(struct devlink_fmsg_item *msg, struct sk_buff *skb)
{
	switch (msg->nla_type) {
	case NLA_FLAG:
	case NLA_U8:
	case NLA_U32:
	case NLA_U64:
	case NLA_NUL_STRING:
	case NLA_BINARY:
		return nla_put_u8(skb, DEVLINK_ATTR_FMSG_OBJ_VALUE_TYPE,
				  msg->nla_type);
	default:
		return -EINVAL;
	}
}