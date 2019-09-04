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
struct rtl_ep_map {int* ep_mapping; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t RTL_TXQ_BCN ; 
 size_t RTL_TXQ_BE ; 
 size_t RTL_TXQ_BK ; 
 size_t RTL_TXQ_HI ; 
 size_t RTL_TXQ_MGT ; 
 size_t RTL_TXQ_VI ; 
 size_t RTL_TXQ_VO ; 

__attribute__((used)) static void _OneOutEpMapping(struct ieee80211_hw *hw, struct rtl_ep_map *ep_map)
{
	ep_map->ep_mapping[RTL_TXQ_BE]	= 2;
	ep_map->ep_mapping[RTL_TXQ_BK]	= 2;
	ep_map->ep_mapping[RTL_TXQ_VI]	= 2;
	ep_map->ep_mapping[RTL_TXQ_VO] = 2;
	ep_map->ep_mapping[RTL_TXQ_MGT] = 2;
	ep_map->ep_mapping[RTL_TXQ_BCN] = 2;
	ep_map->ep_mapping[RTL_TXQ_HI]	= 2;
}