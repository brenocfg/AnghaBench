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
typedef  scalar_t__ u32 ;

/* Variables and functions */
#define  READ_10 138 
#define  READ_12 137 
#define  READ_16 136 
#define  VERIFY 135 
#define  VERIFY_12 134 
#define  VERIFY_16 133 
#define  WRITE_10 132 
#define  WRITE_12 131 
#define  WRITE_16 130 
#define  WRITE_VERIFY 129 
#define  WRITE_VERIFY_12 128 
 scalar_t__ get_unaligned_be16 (int*) ; 
 scalar_t__ get_unaligned_be32 (int*) ; 

__attribute__((used)) static bool is_zero_length_transfer(u8 *cdb)
{
	u32 block_cnt;

	/* Block zero-length transfer sizes on certain commands. */
	switch (cdb[0]) {
	case READ_10:
	case WRITE_10:
	case VERIFY:		/* 0x2F */
	case WRITE_VERIFY:	/* 0x2E */
		block_cnt = get_unaligned_be16(&cdb[7]);
		break;
	case READ_12:
	case WRITE_12:
	case VERIFY_12: /* 0xAF */
	case WRITE_VERIFY_12:	/* 0xAE */
		block_cnt = get_unaligned_be32(&cdb[6]);
		break;
	case READ_16:
	case WRITE_16:
	case VERIFY_16:		/* 0x8F */
		block_cnt = get_unaligned_be32(&cdb[10]);
		break;
	default:
		return false;
	}

	return block_cnt == 0;
}