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

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_seq_lock ; 
 int /*<<< orphan*/  ieee802154_seq_num ; 
 int /*<<< orphan*/  nl802154_family ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct sk_buff *ieee802154_nl_create(int flags, u8 req)
{
	void *hdr;
	struct sk_buff *msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	unsigned long f;

	if (!msg)
		return NULL;

	spin_lock_irqsave(&ieee802154_seq_lock, f);
	hdr = genlmsg_put(msg, 0, ieee802154_seq_num++,
			  &nl802154_family, flags, req);
	spin_unlock_irqrestore(&ieee802154_seq_lock, f);
	if (!hdr) {
		nlmsg_free(msg);
		return NULL;
	}

	return msg;
}