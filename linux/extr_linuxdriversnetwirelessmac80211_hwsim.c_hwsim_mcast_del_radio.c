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
 int /*<<< orphan*/  GENLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWSIM_ATTR_RADIO_ID ; 
 int /*<<< orphan*/  HWSIM_ATTR_RADIO_NAME ; 
 int /*<<< orphan*/  HWSIM_CMD_DEL_RADIO ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwsim_genl_family ; 
 int /*<<< orphan*/  hwsim_mcast_config_msg (struct sk_buff*,struct genl_info*) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void hwsim_mcast_del_radio(int id, const char *hwname,
				  struct genl_info *info)
{
	struct sk_buff *skb;
	void *data;
	int ret;

	skb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!skb)
		return;

	data = genlmsg_put(skb, 0, 0, &hwsim_genl_family, 0,
			   HWSIM_CMD_DEL_RADIO);
	if (!data)
		goto error;

	ret = nla_put_u32(skb, HWSIM_ATTR_RADIO_ID, id);
	if (ret < 0)
		goto error;

	ret = nla_put(skb, HWSIM_ATTR_RADIO_NAME, strlen(hwname),
		      hwname);
	if (ret < 0)
		goto error;

	genlmsg_end(skb, data);

	hwsim_mcast_config_msg(skb, info);

	return;

error:
	nlmsg_free(skb);
}