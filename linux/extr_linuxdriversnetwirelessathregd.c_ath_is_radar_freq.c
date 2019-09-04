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
typedef  int u16 ;
struct ath_regulatory {scalar_t__ country_code; } ;

/* Variables and functions */
 scalar_t__ CTRY_INDIA ; 

__attribute__((used)) static bool ath_is_radar_freq(u16 center_freq,
			      struct ath_regulatory *reg)

{
	if (reg->country_code == CTRY_INDIA)
		return (center_freq >= 5500 && center_freq <= 5700);
	return (center_freq >= 5260 && center_freq <= 5700);
}