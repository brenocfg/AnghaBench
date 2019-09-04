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

/* Variables and functions */
 char* strdup (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

char *get_status_regs_and_bits(char *reg_arg, int reg_bit) {
  char *res = NULL;
  if(!strncmp(reg_arg, "ST0", 3)) {
    switch(reg_bit) {
	case 0:
		res = "st0_dp07";
		break;
	case 1:
		res = "st0_dp08";
		break;
	case 2:
		res = "st0_dp09";
		break;
	case 3:
		res = "st0_dp10";
		break;
	case 4:
		res = "st0_dp11";
		break;
	case 5:
		res = "st0_dp12";
		break;
	case 6:
		res = "st0_dp13";
		break;
	case 7:
		res = "st0_dp14";
		break;
	case 8:
		res = "st0_dp15";
		break;
	case 9:
		res = "st0_acov1";
		break;
	case 10:
		res = "st0_acov0";
		break;
	case 11:
		res = "st0_carry";
		break;
	case 12:
		res = "st0_tc2";
		break;
	case 13:
		res = "st0_tc1";
		break;
	case 14:
		res = "st0_acov3";
		break;
	case 15:
		res = "st0_acov2";
		break;
    }
  } else if(!strncmp(reg_arg, "ST1", 3)) {
		switch(reg_bit) {
		case 0:
			res = "st1_dr2_00";
			break;
		case 1:
			res =  "st1_dr2_01";
			break;
		case 2:
			res = "st1_dr2_02";
			break;
		case 3:
			res = "st1_dr2_03";
			break;
		case 4:
			res = "st1_dr2_04";
			break;
		case 5:
			res = "st1_c54cm";
			break;
		case 6:
			res = "st1_frct";
			break;
		case 7:
			res = "st1_c16";
			break;
		case 8:
			res = "st1_sxmd";
			break;
		case 9:
			res = "st1_satd";
			break;
		case 10:
			res = "st1_m40";
			break;
		case 11:
			res = "st1_intm";
			break;
		case 12:
			res = "st1_hm";
			break;
		case 13:
			res = "st1_xf";
			break;
		case 14:
			res = "st1_cpl";
			break;
		case 15:
			res = "st1_braf";
			break;
      }
  } else if(!strncmp(reg_arg, "ST2", 3)) {
		switch ( reg_bit ) {
		case 0:
			res = "st2_ar0lc";
			break;
		case 1:
			res = "st2_ar1lc";
			break;
		case 2:
			res = "st2_ar2lc";
			break;
		case 3:
			res = "st2_ar3lc";
			break;
		case 4:
			res = "st2_ar4lc";
			break;
		case 5:
			res = "st2_ar5lc";
			break;
		case 6:
			res = "st2_ar6lc";
			break;
		case 7:
			res = "st2_ar7lc";
			break;
		case 8:
			res = "st2_cdplc";
			break;
		case 9:
			res = "st2_govf";
			break;
		case 10:
			res = "st2_rdm";
			break;
		case 11:
			res = "st2_eallow";
			break;
		case 12:
			res = "st2_dbgm";
			break;
		case 13:
			res = "st2_xcnd";
			break;
		case 14:
			res = "st2_xcna";
			break;
		case 15:
			res = "st2_arms";
			break;
       }
  } else if (!strncmp(reg_arg, "ST3", 3)) {
		switch (reg_bit) {
		case 0:
			res = "st3_sst";
			break;
		case 1:
			res = "st3_smul";
			break;
		case 2:
			res = "st3_clkoff";
			break;
		case 3:
			res = "st3_bptr";
			break;
		case 4:
			res = "st3_avis";
			break;
		case 5:
			res = "st3_sata";
			break;
		case 6:
			res = "st3_mpnmc";
			break;
		case 7:
			res = "st3_cberr";
			break;
		case 8:
			res = "st3_homp";
			break;
		case 9:
			res = "st3_homr";
			break;
		case 10:
			res = "st3_homx";
			break;
		case 11:
			res = "st3_homy";
			break;
		case 12:
			res = "st3_hint";
			break;
		case 13:
			res = "st3_caclr";
			break;
		case 14:
			res = "st3_caen";
			break;
		case 15:
			res = "st3_cafrz";
			break;
        }
  }

  if (res != NULL) {
	  res = strdup (res);
  }

  return res;
}