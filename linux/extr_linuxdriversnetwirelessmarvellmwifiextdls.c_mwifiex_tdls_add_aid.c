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
struct mwifiex_private {int /*<<< orphan*/  assoc_rsp_buf; } ;
struct ieee_types_assoc_rsp {int /*<<< orphan*/  a_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_AID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void mwifiex_tdls_add_aid(struct mwifiex_private *priv,
				struct sk_buff *skb)
{
	struct ieee_types_assoc_rsp *assoc_rsp;
	u8 *pos;

	assoc_rsp = (struct ieee_types_assoc_rsp *)&priv->assoc_rsp_buf;
	pos = skb_put(skb, 4);
	*pos++ = WLAN_EID_AID;
	*pos++ = 2;
	memcpy(pos, &assoc_rsp->a_id, sizeof(assoc_rsp->a_id));

	return;
}