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
struct btc_coexist {int (* btc_read_1byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_4byte ) (struct btc_coexist*,int,int) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int halbtc8822b1ant_ltecoex_indirect_read_reg (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int stub1 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 
 int stub4 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int,int) ; 

__attribute__((used)) static void
halbtc8822b1ant_ltecoex_indirect_write_reg(struct btc_coexist *btcoexist,
					   u16 reg_addr, u32 bit_mask,
					   u32 reg_value)
{
	u32 val, i = 0, bitpos = 0, delay_count = 0;

	if (bit_mask == 0x0)
		return;

	if (bit_mask == 0xffffffff) {
		/* wait for ready bit before access 0x1700/0x1704 */
		while (1) {
			if ((btcoexist->btc_read_1byte(btcoexist, 0x1703) &
			     BIT(5)) == 0) {
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

		btcoexist->btc_write_4byte(btcoexist, 0x1704,
					   reg_value); /* put write data */

		btcoexist->btc_write_4byte(btcoexist, 0x1700,
					   0xc00F0000 | reg_addr);
	} else {
		for (i = 0; i <= 31; i++) {
			if (((bit_mask >> i) & 0x1) == 0x1) {
				bitpos = i;
				break;
			}
		}

		/* read back register value before write */
		val = halbtc8822b1ant_ltecoex_indirect_read_reg(btcoexist,
								reg_addr);
		val = (val & (~bit_mask)) | (reg_value << bitpos);

		/* wait for ready bit before access 0x1700/0x1704 */
		while (1) {
			if ((btcoexist->btc_read_1byte(btcoexist, 0x1703) &
			     BIT(5)) == 0) {
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

		btcoexist->btc_write_4byte(btcoexist, 0x1704,
					   val); /* put write data */

		btcoexist->btc_write_4byte(btcoexist, 0x1700,
					   0xc00F0000 | reg_addr);
	}
}