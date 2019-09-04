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
typedef  scalar_t__ u16 ;
struct rtl_priv {int dummy; } ;
struct pgpkt_struct {int offset; int word_en; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_PG ; 
 int EFUSE_REPEAT_THRESHOLD_ ; 
 int /*<<< orphan*/  FEEPROM ; 
 int PG_STATE_DATA ; 
 int PG_STATE_HEADER ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int efuse_calculate_word_cnts (int) ; 
 scalar_t__ efuse_get_current_size (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  efuse_one_byte_read (struct ieee80211_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  efuse_one_byte_write (struct ieee80211_hw*,scalar_t__,int) ; 
 scalar_t__ efuse_pg_packet_read (struct ieee80211_hw*,int,int*) ; 
 int /*<<< orphan*/  efuse_pg_packet_write (struct ieee80211_hw*,int,int,int*) ; 
 int enable_efuse_data_write (struct ieee80211_hw*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void efuse_write_data_case2(struct ieee80211_hw *hw, u16 *efuse_addr,
				   int *continual, u8 *write_state,
				   struct pgpkt_struct target_pkt,
				   int *repeat_times, int *result)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct pgpkt_struct tmp_pkt;
	u8 pg_header;
	u8 tmp_header;
	u8 originaldata[8 * sizeof(u8)];
	u8 tmp_word_cnts;
	u8 badworden = 0x0F;

	pg_header = ((target_pkt.offset << 4) & 0xf0) | target_pkt.word_en;
	efuse_one_byte_write(hw, *efuse_addr, pg_header);
	efuse_one_byte_read(hw, *efuse_addr, &tmp_header);

	if (tmp_header == pg_header) {
		*write_state = PG_STATE_DATA;
	} else if (tmp_header == 0xFF) {
		*write_state = PG_STATE_HEADER;
		*repeat_times += 1;
		if (*repeat_times > EFUSE_REPEAT_THRESHOLD_) {
			*continual = false;
			*result = false;
		}
	} else {
		tmp_pkt.offset = (tmp_header >> 4) & 0x0F;
		tmp_pkt.word_en = tmp_header & 0x0F;

		tmp_word_cnts = efuse_calculate_word_cnts(tmp_pkt.word_en);

		memset(originaldata, 0xff,  8 * sizeof(u8));

		if (efuse_pg_packet_read(hw, tmp_pkt.offset, originaldata)) {
			badworden = enable_efuse_data_write(hw,
							    *efuse_addr + 1,
							    tmp_pkt.word_en,
							    originaldata);

			if (0x0F != (badworden & 0x0F)) {
				u8 reorg_offset = tmp_pkt.offset;
				u8 reorg_worden = badworden;

				efuse_pg_packet_write(hw, reorg_offset,
						      reorg_worden,
						      originaldata);
				*efuse_addr = efuse_get_current_size(hw);
			} else {
				*efuse_addr = *efuse_addr +
					      (tmp_word_cnts * 2) + 1;
			}
		} else {
			*efuse_addr = *efuse_addr + (tmp_word_cnts * 2) + 1;
		}

		*write_state = PG_STATE_HEADER;
		*repeat_times += 1;
		if (*repeat_times > EFUSE_REPEAT_THRESHOLD_) {
			*continual = false;
			*result = false;
		}

		RTPRINT(rtlpriv, FEEPROM, EFUSE_PG,
			"efuse PG_STATE_HEADER-2\n");
	}
}