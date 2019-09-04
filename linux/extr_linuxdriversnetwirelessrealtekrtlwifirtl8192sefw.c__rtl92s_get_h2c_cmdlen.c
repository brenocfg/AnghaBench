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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ H2C_TX_CMD_HDR_LEN ; 
 scalar_t__ N_BYTE_ALIGMENT (scalar_t__,int) ; 

__attribute__((used)) static u32 _rtl92s_get_h2c_cmdlen(u32 h2cbufferlen, u32 cmd_num, u32 *pcmd_len)
{
	u32 totallen = 0, len = 0, tx_desclen = 0;
	u8 i = 0;

	do {
		/* 8 - Byte alignment */
		len = H2C_TX_CMD_HDR_LEN + N_BYTE_ALIGMENT(pcmd_len[i], 8);

		/* Buffer length is not enough */
		if (h2cbufferlen < totallen + len + tx_desclen)
			break;

		totallen += len;
	} while (++i < cmd_num);

	return totallen + tx_desclen;
}