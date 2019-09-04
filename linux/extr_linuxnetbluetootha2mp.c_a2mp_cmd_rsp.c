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
struct amp_mgr {int dummy; } ;
struct a2mp_cmd {int /*<<< orphan*/  len; int /*<<< orphan*/  code; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int a2mp_cmd_rsp(struct amp_mgr *mgr, struct sk_buff *skb,
			       struct a2mp_cmd *hdr)
{
	BT_DBG("ident %d code 0x%2.2x", hdr->ident, hdr->code);

	skb_pull(skb, le16_to_cpu(hdr->len));
	return 0;
}