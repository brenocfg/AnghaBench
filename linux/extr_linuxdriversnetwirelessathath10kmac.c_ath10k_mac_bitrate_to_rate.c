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
 int BIT (int) ; 
 int DIV_ROUND_UP (int,int) ; 
 scalar_t__ ath10k_mac_bitrate_is_cck (int) ; 

__attribute__((used)) static u8 ath10k_mac_bitrate_to_rate(int bitrate)
{
	return DIV_ROUND_UP(bitrate, 5) |
	       (ath10k_mac_bitrate_is_cck(bitrate) ? BIT(7) : 0);
}