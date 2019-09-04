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
typedef  size_t u32 ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int IS_92C_SERIAL (int /*<<< orphan*/ ) ; 
 size_t MAX_TOLERANCE ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static bool _rtl92c_phy_simularity_compare(struct ieee80211_hw *hw,
					   long result[][8], u8 c1, u8 c2)
{
	u32 i, j, diff, simularity_bitmap, bound;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	u8 final_candidate[2] = { 0xFF, 0xFF };
	bool bresult = true, is2t = IS_92C_SERIAL(rtlhal->version);

	if (is2t)
		bound = 8;
	else
		bound = 4;

	simularity_bitmap = 0;

	for (i = 0; i < bound; i++) {
		diff = (result[c1][i] > result[c2][i]) ?
		    (result[c1][i] - result[c2][i]) :
		    (result[c2][i] - result[c1][i]);

		if (diff > MAX_TOLERANCE) {
			if ((i == 2 || i == 6) && !simularity_bitmap) {
				if (result[c1][i] + result[c1][i + 1] == 0)
					final_candidate[(i / 4)] = c2;
				else if (result[c2][i] + result[c2][i + 1] == 0)
					final_candidate[(i / 4)] = c1;
				else
					simularity_bitmap = simularity_bitmap |
					    (1 << i);
			} else
				simularity_bitmap =
				    simularity_bitmap | (1 << i);
		}
	}

	if (simularity_bitmap == 0) {
		for (i = 0; i < (bound / 4); i++) {
			if (final_candidate[i] != 0xFF) {
				for (j = i * 4; j < (i + 1) * 4 - 2; j++)
					result[3][j] =
					    result[final_candidate[i]][j];
				bresult = false;
			}
		}
		return bresult;
	} else if (!(simularity_bitmap & 0x0F)) {
		for (i = 0; i < 4; i++)
			result[3][i] = result[c1][i];
		return false;
	} else if (!(simularity_bitmap & 0xF0) && is2t) {
		for (i = 4; i < 8; i++)
			result[3][i] = result[c1][i];
		return false;
	} else {
		return false;
	}
}