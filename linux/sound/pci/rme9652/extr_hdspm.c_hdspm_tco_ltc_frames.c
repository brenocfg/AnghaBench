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
struct hdspm {int dummy; } ;

/* Variables and functions */
 scalar_t__ HDSPM_RD_TCO ; 
#define  HDSPM_TCO1_LTC_Format_LSB 129 
#define  HDSPM_TCO1_LTC_Format_MSB 128 
 int HDSPM_TCO1_LTC_Input_valid ; 
 int fps_24 ; 
 int fps_25 ; 
 int fps_2997 ; 
 int fps_30 ; 
 int hdspm_read (struct hdspm*,scalar_t__) ; 

__attribute__((used)) static int hdspm_tco_ltc_frames(struct hdspm *hdspm)
{
	u32 status;
	int ret = 0;

	status = hdspm_read(hdspm, HDSPM_RD_TCO + 4);
	if (status & HDSPM_TCO1_LTC_Input_valid) {
		switch (status & (HDSPM_TCO1_LTC_Format_LSB |
					HDSPM_TCO1_LTC_Format_MSB)) {
		case 0:
			/* 24 fps */
			ret = fps_24;
			break;
		case HDSPM_TCO1_LTC_Format_LSB:
			/* 25 fps */
			ret = fps_25;
			break;
		case HDSPM_TCO1_LTC_Format_MSB:
			/* 29.97 fps */
			ret = fps_2997;
			break;
		default:
			/* 30 fps */
			ret = fps_30;
			break;
		}
	}

	return ret;
}