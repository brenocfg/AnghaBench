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
typedef  int u32 ;
typedef  int u16 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_NEXT_PAIR (int,int,int) ; 
 int /*<<< orphan*/  _rtl8188e_config_bb_reg (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  _rtl88e_check_condition (struct ieee80211_hw*,int) ; 

__attribute__((used)) static void handle_branch1(struct ieee80211_hw *hw, u16 arraylen,
			   u32 *array_table)
{
	u32 v1;
	u32 v2;
	int i;

	for (i = 0; i < arraylen; i = i + 2) {
		v1 = array_table[i];
		v2 = array_table[i+1];
		if (v1 < 0xcdcdcdcd) {
			_rtl8188e_config_bb_reg(hw, v1, v2);
		} else { /*This line is the start line of branch.*/
			/* to protect READ_NEXT_PAIR not overrun */
			if (i >= arraylen - 2)
				break;

			if (!_rtl88e_check_condition(hw, array_table[i])) {
				/*Discard the following (offset, data) pairs*/
				READ_NEXT_PAIR(v1, v2, i);
				while (v2 != 0xDEAD &&
				       v2 != 0xCDEF &&
				       v2 != 0xCDCD && i < arraylen - 2)
					READ_NEXT_PAIR(v1, v2, i);
				i -= 2; /* prevent from for-loop += 2*/
			} else { /* Configure matched pairs and skip
				  * to end of if-else.
				  */
				READ_NEXT_PAIR(v1, v2, i);
				while (v2 != 0xDEAD &&
				       v2 != 0xCDEF &&
				       v2 != 0xCDCD && i < arraylen - 2) {
					_rtl8188e_config_bb_reg(hw, v1, v2);
					READ_NEXT_PAIR(v1, v2, i);
				}

				while (v2 != 0xDEAD && i < arraylen - 2)
					READ_NEXT_PAIR(v1, v2, i);
			}
		}
	}
}