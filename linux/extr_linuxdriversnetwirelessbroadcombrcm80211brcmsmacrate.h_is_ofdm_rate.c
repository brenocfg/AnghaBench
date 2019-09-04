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
typedef  size_t u32 ;

/* Variables and functions */
 int BRCMS_RATE_FLAG ; 
 size_t RSPEC_RATE_MASK ; 
 int /*<<< orphan*/  is_mcs_rate (size_t) ; 
 int* rate_info ; 

__attribute__((used)) static inline bool is_ofdm_rate(u32 ratespec)
{
	return !is_mcs_rate(ratespec) &&
	       (rate_info[ratespec & RSPEC_RATE_MASK] & BRCMS_RATE_FLAG);
}