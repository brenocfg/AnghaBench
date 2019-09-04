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
typedef  int u32 ;
typedef  enum qe_clock { ____Placeholder_qe_clock } qe_clock ;

/* Variables and functions */
 int EINVAL ; 
#define  QE_CLK10 143 
#define  QE_CLK11 142 
#define  QE_CLK12 141 
#define  QE_CLK13 140 
#define  QE_CLK14 139 
#define  QE_CLK15 138 
#define  QE_CLK16 137 
#define  QE_CLK17 136 
#define  QE_CLK18 135 
#define  QE_CLK19 134 
#define  QE_CLK21 133 
#define  QE_CLK3 132 
#define  QE_CLK4 131 
#define  QE_CLK6 130 
#define  QE_CLK8 129 
#define  QE_CLK9 128 

__attribute__((used)) static int ucc_get_tdm_tx_clk(u32 tdm_num, enum qe_clock clock)
{
	int clock_bits = -EINVAL;

	switch (tdm_num) {
	case 0:
		switch (clock) {
		case QE_CLK4:
			clock_bits = 6;
			break;
		case QE_CLK9:
			clock_bits = 7;
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (clock) {
		case QE_CLK6:
			clock_bits = 6;
			break;
		case QE_CLK11:
			clock_bits = 7;
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (clock) {
		case QE_CLK8:
			clock_bits = 6;
			break;
		case QE_CLK13:
			clock_bits = 7;
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (clock) {
		case QE_CLK10:
			clock_bits = 6;
			break;
		case QE_CLK15:
			clock_bits = 7;
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (clock) {
		case QE_CLK12:
			clock_bits = 6;
			break;
		case QE_CLK17:
			clock_bits = 7;
			break;
		default:
			break;
		}
		break;
	case 5:
		switch (clock) {
		case QE_CLK14:
			clock_bits = 6;
			break;
		case QE_CLK19:
			clock_bits = 7;
			break;
		default:
			break;
		}
		break;
	case 6:
		switch (clock) {
		case QE_CLK16:
			clock_bits = 6;
			break;
		case QE_CLK21:
			clock_bits = 7;
			break;
		default:
			break;
		}
		break;
	case 7:
		switch (clock) {
		case QE_CLK18:
			clock_bits = 6;
			break;
		case QE_CLK3:
			clock_bits = 7;
			break;
		default:
			break;
		}
		break;
	}

	return clock_bits;
}