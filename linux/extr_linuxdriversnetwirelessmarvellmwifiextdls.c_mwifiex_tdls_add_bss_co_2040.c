#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ieee_types_header {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  element_id; } ;
struct ieee_types_bss_co_2040 {int bss_2040co; TYPE_1__ ieee_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_BSS_COEX_2040 ; 
 struct ieee_types_bss_co_2040* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void mwifiex_tdls_add_bss_co_2040(struct sk_buff *skb)
{
	struct ieee_types_bss_co_2040 *bssco;

	bssco = skb_put(skb, sizeof(struct ieee_types_bss_co_2040));
	bssco->ieee_hdr.element_id = WLAN_EID_BSS_COEX_2040;
	bssco->ieee_hdr.len = sizeof(struct ieee_types_bss_co_2040) -
			      sizeof(struct ieee_types_header);
	bssco->bss_2040co = 0x01;
}