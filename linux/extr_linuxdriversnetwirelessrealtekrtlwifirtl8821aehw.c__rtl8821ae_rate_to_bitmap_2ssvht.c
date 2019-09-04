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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 _rtl8821ae_rate_to_bitmap_2ssvht(__le16 vht_rate)
{
	u8 i, j, tmp_rate;
	u32 rate_bitmap = 0;

	for (i = j = 0; i < 4; i += 2, j += 10) {
		tmp_rate = (le16_to_cpu(vht_rate) >> i) & 3;

		switch (tmp_rate) {
		case 2:
			rate_bitmap = rate_bitmap | (0x03ff << j);
			break;
		case 1:
			rate_bitmap = rate_bitmap | (0x01ff << j);
			break;
		case 0:
			rate_bitmap = rate_bitmap | (0x00ff << j);
			break;
		default:
			break;
		}
	}

	return rate_bitmap;
}