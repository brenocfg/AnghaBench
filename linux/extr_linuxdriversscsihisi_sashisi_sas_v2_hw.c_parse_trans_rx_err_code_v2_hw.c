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

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
#define  RESERVED1 159 
#define  RESERVED2 158 
#define  RESERVED3 157 
#define  RESERVED4 156 
#define  RESERVED5 155 
#define  RESERVED6 154 
#define  RESERVED7 153 
#define  RESERVED8 152 
#define  RESERVED9 151 
#define  TRANS_RX_ERR_WITH_BAD_FRM_TYPE 150 
#define  TRANS_RX_ERR_WITH_BAD_HASH 149 
#define  TRANS_RX_ERR_WITH_BREAK_RECEVIED 148 
#define  TRANS_RX_ERR_WITH_BREAK_REQUEST 147 
#define  TRANS_RX_ERR_WITH_BREAK_TIMEOUT 146 
#define  TRANS_RX_ERR_WITH_CLOSE_COMINIT 145 
#define  TRANS_RX_ERR_WITH_CLOSE_DWS_TIMEOUT 144 
#define  TRANS_RX_ERR_WITH_CLOSE_NORMAL 143 
#define  TRANS_RX_ERR_WITH_CLOSE_PHY_DISABLE 142 
#define  TRANS_RX_ERR_WITH_DATA_LEN0 141 
#define  TRANS_RX_ERR_WITH_LINK_BUF_OVERRUN 140 
#define  TRANS_RX_ERR_WITH_RXFIS_8B10B_DISP_ERR 139 
#define  TRANS_RX_ERR_WITH_RXFIS_CRC_ERR 138 
#define  TRANS_RX_ERR_WITH_RXFIS_DECODE_ERROR 137 
#define  TRANS_RX_ERR_WITH_RXFIS_RX_SYNCP 136 
#define  TRANS_RX_ERR_WITH_RXFRAME_CRC_ERR 135 
#define  TRANS_RX_ERR_WITH_RXFRAME_HAVE_ERRPRM 134 
#define  TRANS_RX_ERR_WITH_RXFRAME_LENGTH_OVERRUN 133 
 int const TRANS_RX_FAIL_BASE ; 
#define  TRANS_RX_R_ERR 132 
#define  TRANS_RX_SMP_FRM_LEN_ERR 131 
#define  TRANS_RX_SMP_RESP_TIMEOUT_ERR 130 
#define  TRANS_RX_SSP_FRM_LEN_ERR 129 
#define  TRANS_RX_XRDY_WLEN_ZERO_ERR 128 

__attribute__((used)) static int parse_trans_rx_err_code_v2_hw(u32 err_msk)
{
	static const u8 trans_rx_err_code_prio[] = {
		TRANS_RX_ERR_WITH_RXFRAME_CRC_ERR,
		TRANS_RX_ERR_WITH_RXFIS_8B10B_DISP_ERR,
		TRANS_RX_ERR_WITH_RXFRAME_HAVE_ERRPRM,
		TRANS_RX_ERR_WITH_RXFIS_DECODE_ERROR,
		TRANS_RX_ERR_WITH_RXFIS_CRC_ERR,
		TRANS_RX_ERR_WITH_RXFRAME_LENGTH_OVERRUN,
		TRANS_RX_ERR_WITH_RXFIS_RX_SYNCP,
		TRANS_RX_ERR_WITH_LINK_BUF_OVERRUN,
		TRANS_RX_ERR_WITH_CLOSE_PHY_DISABLE,
		TRANS_RX_ERR_WITH_CLOSE_DWS_TIMEOUT,
		TRANS_RX_ERR_WITH_CLOSE_COMINIT,
		TRANS_RX_ERR_WITH_BREAK_TIMEOUT,
		TRANS_RX_ERR_WITH_BREAK_REQUEST,
		TRANS_RX_ERR_WITH_BREAK_RECEVIED,
		RESERVED1,
		TRANS_RX_ERR_WITH_CLOSE_NORMAL,
		TRANS_RX_ERR_WITH_DATA_LEN0,
		TRANS_RX_ERR_WITH_BAD_HASH,
		TRANS_RX_XRDY_WLEN_ZERO_ERR,
		TRANS_RX_SSP_FRM_LEN_ERR,
		RESERVED2,
		RESERVED3,
		RESERVED4,
		RESERVED5,
		TRANS_RX_ERR_WITH_BAD_FRM_TYPE,
		TRANS_RX_SMP_FRM_LEN_ERR,
		TRANS_RX_SMP_RESP_TIMEOUT_ERR,
		RESERVED6,
		RESERVED7,
		RESERVED8,
		RESERVED9,
		TRANS_RX_R_ERR,
	};
	int index, i;

	for (i = 0; i < ARRAY_SIZE(trans_rx_err_code_prio); i++) {
		index = trans_rx_err_code_prio[i] - TRANS_RX_FAIL_BASE;
		if (err_msk & (1 << index))
			return trans_rx_err_code_prio[i];
	}
	return -1;
}