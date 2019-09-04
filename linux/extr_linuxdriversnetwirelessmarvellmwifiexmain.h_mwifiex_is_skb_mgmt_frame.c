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
struct sk_buff {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ PKT_TYPE_MGMT ; 
 scalar_t__ get_unaligned_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool mwifiex_is_skb_mgmt_frame(struct sk_buff *skb)
{
	return (get_unaligned_le32(skb->data) == PKT_TYPE_MGMT);
}