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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_MAX_SIZE ; 
 int PGPKT_DATA_SIZE ; 
 int PG_STATE_DATA ; 
 int PG_STATE_HEADER ; 
 scalar_t__ efuse_one_byte_read (struct ieee80211_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  efuse_read_data_case1 (struct ieee80211_hw*,scalar_t__*,int,int,int*,int*) ; 
 int /*<<< orphan*/  efuse_word_enable_data_read (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static int efuse_pg_packet_read(struct ieee80211_hw *hw, u8 offset, u8 *data)
{
	u8 readstate = PG_STATE_HEADER;

	bool continual = true;

	u8 efuse_data, word_cnts = 0;
	u16 efuse_addr = 0;
	u8 tmpdata[8];

	if (data == NULL)
		return false;
	if (offset > 15)
		return false;

	memset(data, 0xff, PGPKT_DATA_SIZE * sizeof(u8));
	memset(tmpdata, 0xff, PGPKT_DATA_SIZE * sizeof(u8));

	while (continual && (efuse_addr < EFUSE_MAX_SIZE)) {
		if (readstate & PG_STATE_HEADER) {
			if (efuse_one_byte_read(hw, efuse_addr, &efuse_data)
			    && (efuse_data != 0xFF))
				efuse_read_data_case1(hw, &efuse_addr,
						      efuse_data, offset,
						      tmpdata, &readstate);
			else
				continual = false;
		} else if (readstate & PG_STATE_DATA) {
			efuse_word_enable_data_read(0, tmpdata, data);
			efuse_addr = efuse_addr + (word_cnts * 2) + 1;
			readstate = PG_STATE_HEADER;
		}

	}

	if ((data[0] == 0xff) && (data[1] == 0xff) &&
	    (data[2] == 0xff) && (data[3] == 0xff) &&
	    (data[4] == 0xff) && (data[5] == 0xff) &&
	    (data[6] == 0xff) && (data[7] == 0xff))
		return false;
	else
		return true;

}