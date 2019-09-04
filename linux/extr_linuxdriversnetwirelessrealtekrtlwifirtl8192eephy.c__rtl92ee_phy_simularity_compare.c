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
typedef  int u32 ;
struct ieee80211_hw {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int MAX_TOLERANCE ; 

__attribute__((used)) static bool _rtl92ee_phy_simularity_compare(struct ieee80211_hw *hw,
					    long result[][8], u8 c1, u8 c2)
{
	u32 i, j, diff, simularity_bitmap, bound;

	u8 final_candidate[2] = { 0xFF, 0xFF };
	bool bresult = true/*, is2t = true*/;
	s32 tmp1, tmp2;

	bound = 8;

	simularity_bitmap = 0;

	for (i = 0; i < bound; i++) {
		if ((i == 1) || (i == 3) || (i == 5) || (i == 7)) {
			if ((result[c1][i] & 0x00000200) != 0)
				tmp1 = result[c1][i] | 0xFFFFFC00;
			else
				tmp1 = result[c1][i];

			if ((result[c2][i] & 0x00000200) != 0)
				tmp2 = result[c2][i] | 0xFFFFFC00;
			else
				tmp2 = result[c2][i];
		} else {
			tmp1 = result[c1][i];
			tmp2 = result[c2][i];
		}

		diff = (tmp1 > tmp2) ? (tmp1 - tmp2) : (tmp2 - tmp1);

		if (diff > MAX_TOLERANCE) {
			if ((i == 2 || i == 6) && !simularity_bitmap) {
				if (result[c1][i] + result[c1][i + 1] == 0)
					final_candidate[(i / 4)] = c2;
				else if (result[c2][i] + result[c2][i + 1] == 0)
					final_candidate[(i / 4)] = c1;
				else
					simularity_bitmap |= (1 << i);
			} else {
				simularity_bitmap |= (1 << i);
			}
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
	}
	if (!(simularity_bitmap & 0x03)) {/*path A TX OK*/
		for (i = 0; i < 2; i++)
			result[3][i] = result[c1][i];
	}
	if (!(simularity_bitmap & 0x0c)) {/*path A RX OK*/
		for (i = 2; i < 4; i++)
			result[3][i] = result[c1][i];
	}
	if (!(simularity_bitmap & 0x30)) {/*path B TX OK*/
		for (i = 4; i < 6; i++)
			result[3][i] = result[c1][i];
	}
	if (!(simularity_bitmap & 0xc0)) {/*path B RX OK*/
		for (i = 6; i < 8; i++)
			result[3][i] = result[c1][i];
	}
	return false;
}