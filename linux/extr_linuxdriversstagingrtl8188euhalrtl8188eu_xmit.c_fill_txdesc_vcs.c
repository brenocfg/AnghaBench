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
struct pkt_attrib {int vcs_mode; int bwmode; scalar_t__ ch_offset; scalar_t__ ht_en; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int BIT (int) ; 
 int CTS_2_SELF ; 
#define  CTS_TO_SELF 130 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_LOWER ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_UPPER ; 
 int HT_CHANNEL_WIDTH_40 ; 
 int HW_RTS_EN ; 
#define  NONE_VCS 129 
#define  RTS_CTS 128 
 int RTS_EN ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static void fill_txdesc_vcs(struct pkt_attrib *pattrib, __le32 *pdw)
{
	switch (pattrib->vcs_mode) {
	case RTS_CTS:
		*pdw |= cpu_to_le32(RTS_EN);
		break;
	case CTS_TO_SELF:
		*pdw |= cpu_to_le32(CTS_2_SELF);
		break;
	case NONE_VCS:
	default:
		break;
	}
	if (pattrib->vcs_mode) {
		*pdw |= cpu_to_le32(HW_RTS_EN);
		/*  Set RTS BW */
		if (pattrib->ht_en) {
			*pdw |= (pattrib->bwmode&HT_CHANNEL_WIDTH_40) ?	cpu_to_le32(BIT(27)) : 0;

			if (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_LOWER)
				*pdw |= cpu_to_le32((0x01 << 28) & 0x30000000);
			else if (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_UPPER)
				*pdw |= cpu_to_le32((0x02 << 28) & 0x30000000);
			else if (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_DONT_CARE)
				*pdw |= 0;
			else
				*pdw |= cpu_to_le32((0x03 << 28) & 0x30000000);
		}
	}
}