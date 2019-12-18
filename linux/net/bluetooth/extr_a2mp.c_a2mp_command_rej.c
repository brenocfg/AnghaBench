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
struct amp_mgr {int dummy; } ;
struct a2mp_cmd_rej {int /*<<< orphan*/  reason; } ;
struct a2mp_cmd {int /*<<< orphan*/  ident; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int a2mp_command_rej(struct amp_mgr *mgr, struct sk_buff *skb,
			    struct a2mp_cmd *hdr)
{
	struct a2mp_cmd_rej *rej = (void *) skb->data;

	if (le16_to_cpu(hdr->len) < sizeof(*rej))
		return -EINVAL;

	BT_DBG("ident %d reason %d", hdr->ident, le16_to_cpu(rej->reason));

	skb_pull(skb, sizeof(*rej));

	return 0;
}