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
typedef  int /*<<< orphan*/  u16 ;
struct ks_wlan_private {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  SME_FRAGMENTATION_THRESHOLD_REQUEST 140 
#define  SME_GET_EEPROM_CKSUM 139 
#define  SME_MODE_SET_REQUEST 138 
#define  SME_RSN_ENABLED_REQUEST 137 
#define  SME_RTS_THRESHOLD_REQUEST 136 
#define  SME_START_REQUEST 135 
#define  SME_STOP_REQUEST 134 
#define  SME_WEP_FLAG_REQUEST 133 
#define  SME_WEP_INDEX_REQUEST 132 
#define  SME_WEP_KEY1_REQUEST 131 
#define  SME_WEP_KEY2_REQUEST 130 
#define  SME_WEP_KEY3_REQUEST 129 
#define  SME_WEP_KEY4_REQUEST 128 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void ks7010_sme_enqueue_events(struct ks_wlan_private *priv)
{
	static const u16 init_events[] = {
		SME_GET_EEPROM_CKSUM, SME_STOP_REQUEST,
		SME_RTS_THRESHOLD_REQUEST, SME_FRAGMENTATION_THRESHOLD_REQUEST,
		SME_WEP_INDEX_REQUEST, SME_WEP_KEY1_REQUEST,
		SME_WEP_KEY2_REQUEST, SME_WEP_KEY3_REQUEST,
		SME_WEP_KEY4_REQUEST, SME_WEP_FLAG_REQUEST,
		SME_RSN_ENABLED_REQUEST, SME_MODE_SET_REQUEST,
		SME_START_REQUEST
	};
	int ev;

	for (ev = 0; ev < ARRAY_SIZE(init_events); ev++)
		hostif_sme_enqueue(priv, init_events[ev]);
}