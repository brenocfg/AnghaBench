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
struct pkt_attrib {int bwmode; scalar_t__ ch_offset; scalar_t__ ht_en; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int BIT (int) ; 
 int DATA_SC_SHT ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_LOWER ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_UPPER ; 
 int HT_CHANNEL_WIDTH_40 ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static void fill_txdesc_phy(struct pkt_attrib *pattrib, __le32 *pdw)
{
	if (pattrib->ht_en) {
		*pdw |= (pattrib->bwmode&HT_CHANNEL_WIDTH_40) ?	cpu_to_le32(BIT(25)) : 0;

		if (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_LOWER)
			*pdw |= cpu_to_le32((0x01 << DATA_SC_SHT) & 0x003f0000);
		else if (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_UPPER)
			*pdw |= cpu_to_le32((0x02 << DATA_SC_SHT) & 0x003f0000);
		else if (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_DONT_CARE)
			*pdw |= 0;
		else
			*pdw |= cpu_to_le32((0x03 << DATA_SC_SHT) & 0x003f0000);
	}
}