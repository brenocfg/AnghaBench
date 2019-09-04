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
typedef  int u8 ;

/* Variables and functions */
#define  RSI_BT_Q 130 
#define  RSI_COEX_Q 129 
 int RSI_COEX_Q_BT ; 
 int RSI_COEX_Q_COMMON ; 
 int RSI_COEX_Q_INVALID ; 
 int RSI_COEX_Q_WLAN ; 
#define  RSI_WLAN_Q 128 

__attribute__((used)) static inline int rsi_map_coex_q(u8 hal_queue)
{
	switch (hal_queue) {
	case RSI_COEX_Q:
		return RSI_COEX_Q_COMMON;
	case RSI_WLAN_Q:
		return RSI_COEX_Q_WLAN;
	case RSI_BT_Q:
		return RSI_COEX_Q_BT;
	}
	return RSI_COEX_Q_INVALID;
}