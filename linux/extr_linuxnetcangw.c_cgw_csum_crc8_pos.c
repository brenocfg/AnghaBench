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
typedef  size_t u8 ;
struct cgw_csum_crc8 {size_t init_crc_val; int from_idx; int to_idx; size_t* crctab; int profile; size_t* profile_data; size_t result_idx; size_t final_xor_val; } ;
struct can_frame {size_t* data; int can_id; } ;

/* Variables and functions */
#define  CGW_CRC8PRF_16U8 130 
#define  CGW_CRC8PRF_1U8 129 
#define  CGW_CRC8PRF_SFFID_XOR 128 

__attribute__((used)) static void cgw_csum_crc8_pos(struct can_frame *cf, struct cgw_csum_crc8 *crc8)
{
	u8 crc = crc8->init_crc_val;
	int i;

	for (i = crc8->from_idx; i <= crc8->to_idx; i++)
		crc = crc8->crctab[crc^cf->data[i]];

	switch (crc8->profile) {

	case CGW_CRC8PRF_1U8:
		crc = crc8->crctab[crc^crc8->profile_data[0]];
		break;

	case  CGW_CRC8PRF_16U8:
		crc = crc8->crctab[crc^crc8->profile_data[cf->data[1] & 0xF]];
		break;

	case CGW_CRC8PRF_SFFID_XOR:
		crc = crc8->crctab[crc^(cf->can_id & 0xFF)^
				   (cf->can_id >> 8 & 0xFF)];
		break;
	}

	cf->data[crc8->result_idx] = crc^crc8->final_xor_val;
}