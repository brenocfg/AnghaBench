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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int max_patterns; int /*<<< orphan*/  wow_event_mask2; int /*<<< orphan*/  wow_event_mask; } ;
struct ath_hw {TYPE_1__ wow; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MAC_PCU_WOW4 ; 
 int AR_WOW_LEN1_SHIFT (int) ; 
 int AR_WOW_LEN2_SHIFT (int) ; 
 int AR_WOW_LEN3_SHIFT (int) ; 
 int AR_WOW_LEN4_SHIFT (int) ; 
 int /*<<< orphan*/  AR_WOW_LENGTH1 ; 
 int AR_WOW_LENGTH1_MASK (int) ; 
 int /*<<< orphan*/  AR_WOW_LENGTH2 ; 
 int AR_WOW_LENGTH2_MASK (int) ; 
 int /*<<< orphan*/  AR_WOW_LENGTH3 ; 
 int AR_WOW_LENGTH3_MASK (int) ; 
 int /*<<< orphan*/  AR_WOW_LENGTH4 ; 
 int AR_WOW_LENGTH4_MASK (int) ; 
 int AR_WOW_LENGTH_MAX ; 
 int /*<<< orphan*/  AR_WOW_PATTERN ; 
 int AR_WOW_PAT_FOUND_SHIFT ; 
 scalar_t__ AR_WOW_TB_MASK (int) ; 
 scalar_t__ AR_WOW_TB_PATTERN (int) ; 
 int /*<<< orphan*/  BIT (int) ; 
 int ENOSPC ; 
 int MAX_NUM_PATTERN ; 
 int MAX_NUM_PATTERN_LEGACY ; 
 int MAX_PATTERN_MASK_SIZE ; 
 int MAX_PATTERN_SIZE ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

int ath9k_hw_wow_apply_pattern(struct ath_hw *ah, u8 *user_pattern,
			       u8 *user_mask, int pattern_count,
			       int pattern_len)
{
	int i;
	u32 pattern_val, mask_val;
	u32 set, clr;

	if (pattern_count >= ah->wow.max_patterns)
		return -ENOSPC;

	if (pattern_count < MAX_NUM_PATTERN_LEGACY)
		REG_SET_BIT(ah, AR_WOW_PATTERN, BIT(pattern_count));
	else
		REG_SET_BIT(ah, AR_MAC_PCU_WOW4, BIT(pattern_count - 8));

	for (i = 0; i < MAX_PATTERN_SIZE; i += 4) {
		memcpy(&pattern_val, user_pattern, 4);
		REG_WRITE(ah, (AR_WOW_TB_PATTERN(pattern_count) + i),
			  pattern_val);
		user_pattern += 4;
	}

	for (i = 0; i < MAX_PATTERN_MASK_SIZE; i += 4) {
		memcpy(&mask_val, user_mask, 4);
		REG_WRITE(ah, (AR_WOW_TB_MASK(pattern_count) + i), mask_val);
		user_mask += 4;
	}

	if (pattern_count < MAX_NUM_PATTERN_LEGACY)
		ah->wow.wow_event_mask |=
			BIT(pattern_count + AR_WOW_PAT_FOUND_SHIFT);
	else
		ah->wow.wow_event_mask2 |=
			BIT((pattern_count - 8) + AR_WOW_PAT_FOUND_SHIFT);

	if (pattern_count < 4) {
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN1_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH1_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH1, set, clr);
	} else if (pattern_count < 8) {
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN2_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH2_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH2, set, clr);
	} else if (pattern_count < 12) {
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN3_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH3_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH3, set, clr);
	} else if (pattern_count < MAX_NUM_PATTERN) {
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN4_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH4_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH4, set, clr);
	}

	return 0;
}