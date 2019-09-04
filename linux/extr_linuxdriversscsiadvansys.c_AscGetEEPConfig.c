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
typedef  int ushort ;
typedef  int /*<<< orphan*/  uchar ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  int /*<<< orphan*/  ASCEEP_CONFIG ;

/* Variables and functions */
 int ASC_EEP_DVC_CFG_BEG ; 
 int ASC_EEP_DVC_CFG_BEG_VL ; 
 int ASC_EEP_MAX_DVC_ADDR ; 
 int ASC_EEP_MAX_DVC_ADDR_VL ; 
 int ASC_IS_VL ; 
 int AscReadEEPWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int) ; 

__attribute__((used)) static ushort AscGetEEPConfig(PortAddr iop_base, ASCEEP_CONFIG *cfg_buf,
			      ushort bus_type)
{
	ushort wval;
	ushort sum;
	ushort *wbuf;
	int cfg_beg;
	int cfg_end;
	int uchar_end_in_config = ASC_EEP_MAX_DVC_ADDR - 2;
	int s_addr;

	wbuf = (ushort *)cfg_buf;
	sum = 0;
	/* Read two config words; Byte-swapping done by AscReadEEPWord(). */
	for (s_addr = 0; s_addr < 2; s_addr++, wbuf++) {
		*wbuf = AscReadEEPWord(iop_base, (uchar)s_addr);
		sum += *wbuf;
	}
	if (bus_type & ASC_IS_VL) {
		cfg_beg = ASC_EEP_DVC_CFG_BEG_VL;
		cfg_end = ASC_EEP_MAX_DVC_ADDR_VL;
	} else {
		cfg_beg = ASC_EEP_DVC_CFG_BEG;
		cfg_end = ASC_EEP_MAX_DVC_ADDR;
	}
	for (s_addr = cfg_beg; s_addr <= (cfg_end - 1); s_addr++, wbuf++) {
		wval = AscReadEEPWord(iop_base, (uchar)s_addr);
		if (s_addr <= uchar_end_in_config) {
			/*
			 * Swap all char fields - must unswap bytes already swapped
			 * by AscReadEEPWord().
			 */
			*wbuf = le16_to_cpu(wval);
		} else {
			/* Don't swap word field at the end - cntl field. */
			*wbuf = wval;
		}
		sum += wval;	/* Checksum treats all EEPROM data as words. */
	}
	/*
	 * Read the checksum word which will be compared against 'sum'
	 * by the caller. Word field already swapped.
	 */
	*wbuf = AscReadEEPWord(iop_base, (uchar)s_addr);
	return sum;
}