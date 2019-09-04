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
typedef  int /*<<< orphan*/  u8 ;
struct cfg80211_wowlan {size_t n_patterns; struct cfg80211_pkt_pattern* patterns; } ;
struct cfg80211_pkt_pattern {int pattern_len; int /*<<< orphan*/  mask; int /*<<< orphan*/  pattern; } ;
struct ath_softc {struct ath_hw* sc_ah; } ;
struct ath_hw {int dummy; } ;
typedef  size_t s8 ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int MAX_PATTERN_SIZE ; 
 int ath9k_hw_wow_apply_pattern (struct ath_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath9k_wow_add_pattern(struct ath_softc *sc,
				 struct cfg80211_wowlan *wowlan)
{
	struct ath_hw *ah = sc->sc_ah;
	struct cfg80211_pkt_pattern *patterns = wowlan->patterns;
	u8 wow_pattern[MAX_PATTERN_SIZE];
	u8 wow_mask[MAX_PATTERN_SIZE];
	int mask_len, ret = 0;
	s8 i = 0;

	for (i = 0; i < wowlan->n_patterns; i++) {
		mask_len = DIV_ROUND_UP(patterns[i].pattern_len, 8);
		memset(wow_pattern, 0, MAX_PATTERN_SIZE);
		memset(wow_mask, 0, MAX_PATTERN_SIZE);
		memcpy(wow_pattern, patterns[i].pattern, patterns[i].pattern_len);
		memcpy(wow_mask, patterns[i].mask, mask_len);

		ret = ath9k_hw_wow_apply_pattern(ah,
						 wow_pattern,
						 wow_mask,
						 i + 2,
						 patterns[i].pattern_len);
		if (ret)
			break;
	}

	return ret;
}