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
typedef  int u16 ;

/* Variables and functions */
 int BB_TYPE_11A ; 
#define  RATE_12M 135 
#define  RATE_18M 134 
#define  RATE_24M 133 
#define  RATE_36M 132 
#define  RATE_48M 131 
#define  RATE_54M 130 
#define  RATE_6M 129 
#define  RATE_9M 128 

__attribute__((used)) static void vnt_calculate_ofdm_rate(u16 rate, u8 bb_type,
				    u8 *tx_rate, u8 *rsv_time)
{
	switch (rate) {
	case RATE_6M:
		if (bb_type == BB_TYPE_11A) {
			*tx_rate = 0x9b;
			*rsv_time = 24;
		} else {
			*tx_rate = 0x8b;
			*rsv_time = 30;
		}
			break;
	case RATE_9M:
		if (bb_type == BB_TYPE_11A) {
			*tx_rate = 0x9f;
			*rsv_time = 16;
		} else {
			*tx_rate = 0x8f;
			*rsv_time = 22;
		}
		break;
	case RATE_12M:
		if (bb_type == BB_TYPE_11A) {
			*tx_rate = 0x9a;
			*rsv_time = 12;
		} else {
			*tx_rate = 0x8a;
			*rsv_time = 18;
		}
		break;
	case RATE_18M:
		if (bb_type == BB_TYPE_11A) {
			*tx_rate = 0x9e;
			*rsv_time = 8;
		} else {
			*tx_rate = 0x8e;
			*rsv_time = 14;
		}
		break;
	case RATE_36M:
		if (bb_type == BB_TYPE_11A) {
			*tx_rate = 0x9d;
			*rsv_time = 4;
		} else {
			*tx_rate = 0x8d;
			*rsv_time = 10;
		}
		break;
	case RATE_48M:
		if (bb_type == BB_TYPE_11A) {
			*tx_rate = 0x98;
			*rsv_time = 4;
		} else {
			*tx_rate = 0x88;
			*rsv_time = 10;
		}
		break;
	case RATE_54M:
		if (bb_type == BB_TYPE_11A) {
			*tx_rate = 0x9c;
			*rsv_time = 4;
		} else {
			*tx_rate = 0x8c;
			*rsv_time = 10;
		}
		break;
	case RATE_24M:
	default:
		if (bb_type == BB_TYPE_11A) {
			*tx_rate = 0x99;
			*rsv_time = 8;
		} else {
			*tx_rate = 0x89;
			*rsv_time = 14;
		}
		break;
	}
}