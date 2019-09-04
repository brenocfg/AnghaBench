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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 void* genlmsg_put_reply (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl802154_family ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct sk_buff *ieee802154_nl_new_reply(struct genl_info *info,
					int flags, u8 req)
{
	void *hdr;
	struct sk_buff *msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);

	if (!msg)
		return NULL;

	hdr = genlmsg_put_reply(msg, info,
				&nl802154_family, flags, req);
	if (!hdr) {
		nlmsg_free(msg);
		return NULL;
	}

	return msg;
}