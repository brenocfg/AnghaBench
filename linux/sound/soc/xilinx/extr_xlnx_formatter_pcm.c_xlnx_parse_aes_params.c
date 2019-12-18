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
struct device {int dummy; } ;

/* Variables and functions */
 int IEC958_AES0_PROFESSIONAL ; 
 int IEC958_AES0_PRO_FS ; 
#define  IEC958_AES0_PRO_FS_32000 147 
#define  IEC958_AES0_PRO_FS_44100 146 
#define  IEC958_AES0_PRO_FS_48000 145 
#define  IEC958_AES0_PRO_FS_NOTID 144 
 int IEC958_AES2_PRO_SBITS ; 
#define  IEC958_AES2_PRO_SBITS_20 143 
#define  IEC958_AES2_PRO_SBITS_24 142 
 int IEC958_AES2_PRO_WORDLEN ; 
#define  IEC958_AES2_PRO_WORDLEN_20_16 141 
#define  IEC958_AES2_PRO_WORDLEN_22_18 140 
#define  IEC958_AES2_PRO_WORDLEN_23_19 139 
#define  IEC958_AES2_PRO_WORDLEN_24_20 138 
#define  IEC958_AES2_PRO_WORDLEN_NOTID 137 
 int IEC958_AES3_CON_FS ; 
#define  IEC958_AES3_CON_FS_32000 136 
#define  IEC958_AES3_CON_FS_44100 135 
#define  IEC958_AES3_CON_FS_48000 134 
 int IEC958_AES4_CON_MAX_WORDLEN_24 ; 
 int IEC958_AES4_CON_WORDLEN ; 
#define  IEC958_AES4_CON_WORDLEN_20_16 133 
#define  IEC958_AES4_CON_WORDLEN_21_17 132 
#define  IEC958_AES4_CON_WORDLEN_22_18 131 
#define  IEC958_AES4_CON_WORDLEN_23_19 130 
#define  IEC958_AES4_CON_WORDLEN_24_20 129 
#define  IEC958_AES4_CON_WORDLEN_NOTID 128 
 int XLNX_PARAM_UNKNOWN ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 

__attribute__((used)) static void xlnx_parse_aes_params(u32 chsts_reg1_val, u32 chsts_reg2_val,
				  struct device *dev)
{
	u32 padded, srate, bit_depth, status[2];

	if (chsts_reg1_val & IEC958_AES0_PROFESSIONAL) {
		status[0] = chsts_reg1_val & 0xff;
		status[1] = (chsts_reg1_val >> 16) & 0xff;

		switch (status[0] & IEC958_AES0_PRO_FS) {
		case IEC958_AES0_PRO_FS_44100:
			srate = 44100;
			break;
		case IEC958_AES0_PRO_FS_48000:
			srate = 48000;
			break;
		case IEC958_AES0_PRO_FS_32000:
			srate = 32000;
			break;
		case IEC958_AES0_PRO_FS_NOTID:
		default:
			srate = XLNX_PARAM_UNKNOWN;
			break;
		}

		switch (status[1] & IEC958_AES2_PRO_SBITS) {
		case IEC958_AES2_PRO_WORDLEN_NOTID:
		case IEC958_AES2_PRO_SBITS_20:
			padded = 0;
			break;
		case IEC958_AES2_PRO_SBITS_24:
			padded = 4;
			break;
		default:
			bit_depth = XLNX_PARAM_UNKNOWN;
			goto log_params;
		}

		switch (status[1] & IEC958_AES2_PRO_WORDLEN) {
		case IEC958_AES2_PRO_WORDLEN_20_16:
			bit_depth = 16 + padded;
			break;
		case IEC958_AES2_PRO_WORDLEN_22_18:
			bit_depth = 18 + padded;
			break;
		case IEC958_AES2_PRO_WORDLEN_23_19:
			bit_depth = 19 + padded;
			break;
		case IEC958_AES2_PRO_WORDLEN_24_20:
			bit_depth = 20 + padded;
			break;
		case IEC958_AES2_PRO_WORDLEN_NOTID:
		default:
			bit_depth = XLNX_PARAM_UNKNOWN;
			break;
		}

	} else {
		status[0] = (chsts_reg1_val >> 24) & 0xff;
		status[1] = chsts_reg2_val & 0xff;

		switch (status[0] & IEC958_AES3_CON_FS) {
		case IEC958_AES3_CON_FS_44100:
			srate = 44100;
			break;
		case IEC958_AES3_CON_FS_48000:
			srate = 48000;
			break;
		case IEC958_AES3_CON_FS_32000:
			srate = 32000;
			break;
		default:
			srate = XLNX_PARAM_UNKNOWN;
			break;
		}

		if (status[1] & IEC958_AES4_CON_MAX_WORDLEN_24)
			padded = 4;
		else
			padded = 0;

		switch (status[1] & IEC958_AES4_CON_WORDLEN) {
		case IEC958_AES4_CON_WORDLEN_20_16:
			bit_depth = 16 + padded;
			break;
		case IEC958_AES4_CON_WORDLEN_22_18:
			bit_depth = 18 + padded;
			break;
		case IEC958_AES4_CON_WORDLEN_23_19:
			bit_depth = 19 + padded;
			break;
		case IEC958_AES4_CON_WORDLEN_24_20:
			bit_depth = 20 + padded;
			break;
		case IEC958_AES4_CON_WORDLEN_21_17:
			bit_depth = 17 + padded;
			break;
		case IEC958_AES4_CON_WORDLEN_NOTID:
		default:
			bit_depth = XLNX_PARAM_UNKNOWN;
			break;
		}
	}

log_params:
	if (srate != XLNX_PARAM_UNKNOWN)
		dev_info(dev, "sample rate = %d\n", srate);
	else
		dev_info(dev, "sample rate = unknown\n");

	if (bit_depth != XLNX_PARAM_UNKNOWN)
		dev_info(dev, "bit_depth = %d\n", bit_depth);
	else
		dev_info(dev, "bit_depth = unknown\n");
}