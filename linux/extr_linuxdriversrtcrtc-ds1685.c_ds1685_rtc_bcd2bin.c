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
struct ds1685_priv {scalar_t__ bcd_mode; } ;

/* Variables and functions */
 int bcd2bin (int) ; 

__attribute__((used)) static inline u8
ds1685_rtc_bcd2bin(struct ds1685_priv *rtc, u8 val, u8 bcd_mask, u8 bin_mask)
{
	if (rtc->bcd_mode)
		return (bcd2bin(val) & bcd_mask);

	return (val & bin_mask);
}