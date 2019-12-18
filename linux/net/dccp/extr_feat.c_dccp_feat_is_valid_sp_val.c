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

/* Variables and functions */
 int DCCPC_CCID2 ; 
 int DCCPC_CCID3 ; 
#define  DCCPF_CCID 135 
#define  DCCPF_DATA_CHECKSUM 134 
#define  DCCPF_ECN_INCAPABLE 133 
#define  DCCPF_MIN_CSUM_COVER 132 
#define  DCCPF_SEND_ACK_VECTOR 131 
#define  DCCPF_SEND_LEV_RATE 130 
#define  DCCPF_SEND_NDP_COUNT 129 
#define  DCCPF_SHORT_SEQNOS 128 

__attribute__((used)) static u8 dccp_feat_is_valid_sp_val(u8 feat_num, u8 val)
{
	switch (feat_num) {
	case DCCPF_CCID:
		return val == DCCPC_CCID2 || val == DCCPC_CCID3;
	/* Type-check Boolean feature values: */
	case DCCPF_SHORT_SEQNOS:
	case DCCPF_ECN_INCAPABLE:
	case DCCPF_SEND_ACK_VECTOR:
	case DCCPF_SEND_NDP_COUNT:
	case DCCPF_DATA_CHECKSUM:
	case DCCPF_SEND_LEV_RATE:
		return val < 2;
	case DCCPF_MIN_CSUM_COVER:
		return val < 16;
	}
	return 0;			/* feature unknown */
}