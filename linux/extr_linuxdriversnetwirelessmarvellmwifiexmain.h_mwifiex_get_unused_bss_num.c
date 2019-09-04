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
typedef  size_t u8 ;
struct mwifiex_adapter {size_t priv_num; TYPE_1__** priv; } ;
typedef  int /*<<< orphan*/  index ;
struct TYPE_2__ {size_t bss_type; scalar_t__ bss_mode; size_t bss_num; } ;

/* Variables and functions */
 int MWIFIEX_MAX_BSS_NUM ; 
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u8
mwifiex_get_unused_bss_num(struct mwifiex_adapter *adapter, u8 bss_type)
{
	u8 i, j;
	int index[MWIFIEX_MAX_BSS_NUM];

	memset(index, 0, sizeof(index));
	for (i = 0; i < adapter->priv_num; i++)
		if (adapter->priv[i]) {
			if (adapter->priv[i]->bss_type == bss_type &&
			    !(adapter->priv[i]->bss_mode ==
			      NL80211_IFTYPE_UNSPECIFIED)) {
				index[adapter->priv[i]->bss_num] = 1;
			}
		}
	for (j = 0; j < MWIFIEX_MAX_BSS_NUM; j++)
		if (!index[j])
			return j;
	return -1;
}