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
struct btc_coexist {int (* btc_read_1byte ) (struct btc_coexist*,int) ;int (* btc_read_4byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_4byte ) (struct btc_coexist*,int,int) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int stub1 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int) ; 
 int stub3 (struct btc_coexist*,int) ; 

__attribute__((used)) static u32
halbtc8822b2ant_ltecoex_indirect_read_reg(struct btc_coexist *btcoexist,
					  u16 reg_addr)
{
	u32 delay_count = 0;

	while (1) {
		if ((btcoexist->btc_read_1byte(btcoexist, 0x1703) & BIT(5)) ==
		    0) {
			mdelay(50);
			delay_count++;
			if (delay_count >= 10) {
				delay_count = 0;
				break;
			}
		} else {
			break;
		}
	}

	/* wait for ready bit before access 0x1700		 */
	btcoexist->btc_write_4byte(btcoexist, 0x1700, 0x800F0000 | reg_addr);

	return btcoexist->btc_read_4byte(btcoexist, 0x1708); /* get read data */
}