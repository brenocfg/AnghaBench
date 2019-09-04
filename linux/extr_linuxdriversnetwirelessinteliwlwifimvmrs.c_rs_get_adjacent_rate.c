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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {int prev_rs; int next_rs; } ;

/* Variables and functions */
 int BIT (int) ; 
 int IWL_RATE_COUNT ; 
 int IWL_RATE_INVALID ; 
 scalar_t__ is_type_a_band (int) ; 
 int /*<<< orphan*/  is_type_legacy (int) ; 
 TYPE_1__* iwl_rates ; 

__attribute__((used)) static u16 rs_get_adjacent_rate(struct iwl_mvm *mvm, u8 index, u16 rate_mask,
				int rate_type)
{
	u8 high = IWL_RATE_INVALID;
	u8 low = IWL_RATE_INVALID;

	/* 802.11A or ht walks to the next literal adjacent rate in
	 * the rate table */
	if (is_type_a_band(rate_type) || !is_type_legacy(rate_type)) {
		int i;
		u32 mask;

		/* Find the previous rate that is in the rate mask */
		i = index - 1;
		if (i >= 0)
			mask = BIT(i);
		for (; i >= 0; i--, mask >>= 1) {
			if (rate_mask & mask) {
				low = i;
				break;
			}
		}

		/* Find the next rate that is in the rate mask */
		i = index + 1;
		for (mask = (1 << i); i < IWL_RATE_COUNT; i++, mask <<= 1) {
			if (rate_mask & mask) {
				high = i;
				break;
			}
		}

		return (high << 8) | low;
	}

	low = index;
	while (low != IWL_RATE_INVALID) {
		low = iwl_rates[low].prev_rs;
		if (low == IWL_RATE_INVALID)
			break;
		if (rate_mask & (1 << low))
			break;
	}

	high = index;
	while (high != IWL_RATE_INVALID) {
		high = iwl_rates[high].next_rs;
		if (high == IWL_RATE_INVALID)
			break;
		if (rate_mask & (1 << high))
			break;
	}

	return (high << 8) | low;
}