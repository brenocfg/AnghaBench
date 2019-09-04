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
typedef  int /*<<< orphan*/  u16 ;
struct phy_dm_struct {int /*<<< orphan*/  debug_components; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCMD_DECIMAL ; 
 int /*<<< orphan*/  DCMD_HEX ; 
 int /*<<< orphan*/  ODM_COMP_API ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,...) ; 
 int /*<<< orphan*/  PHYDM_SSCANF (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  phydm_psd (struct phy_dm_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_psd_para_setting (struct phy_dm_struct*,int,int,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

void phydm_psd_debug(void *dm_void, char input[][16], u32 *_used, char *output,
		     u32 *_out_len, u32 input_num)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	char help[] = "-h";
	u32 var1[10] = {0};
	u32 used = *_used;
	u32 out_len = *_out_len;
	u8 i;

	if ((strcmp(input[1], help) == 0)) {
		PHYDM_SNPRINTF(
			output + used, out_len - used,
			"{0} {sw_avg} {hw_avg 0:3} {1:I,2:Q,3:IQ} {fft_point: 128*(1:4)} {path_sel 0~3} {0:ADC, 1:RXIQC} {CH} {noise_k}\n");
		PHYDM_SNPRINTF(output + used, out_len - used,
			       "{1} {IGI(hex)} {start_point} {stop_point}\n");
		return;
	}

	PHYDM_SSCANF(input[1], DCMD_DECIMAL, &var1[0]);

	if (var1[0] == 0) {
		for (i = 1; i < 10; i++) {
			if (input[i + 1])
				PHYDM_SSCANF(input[i + 1], DCMD_DECIMAL,
					     &var1[i]);
		}

		PHYDM_SNPRINTF(
			output + used, out_len - used,
			"sw_avg_time=((%d)), hw_avg_time=((%d)), IQ=((%d)), fft=((%d)), path=((%d)), input =((%d)) ch=((%d)), noise_k=((%d))\n",
			var1[1], var1[2], var1[3], var1[4], var1[5], var1[6],
			(u8)var1[7], (u8)var1[8]);
		phydm_psd_para_setting(dm, (u8)var1[1], (u8)var1[2],
				       (u8)var1[3], (u16)var1[4], (u8)var1[5],
				       (u8)var1[6], (u8)var1[7], (u8)var1[8]);

	} else if (var1[0] == 1) {
		PHYDM_SSCANF(input[2], DCMD_HEX, &var1[1]);
		PHYDM_SSCANF(input[3], DCMD_DECIMAL, &var1[2]);
		PHYDM_SSCANF(input[4], DCMD_DECIMAL, &var1[3]);
		PHYDM_SNPRINTF(
			output + used, out_len - used,
			"IGI=((0x%x)), start_point=((%d)), stop_point=((%d))\n",
			var1[1], var1[2], var1[3]);
		dm->debug_components |= ODM_COMP_API;
		phydm_psd(dm, var1[1], (u16)var1[2], (u16)var1[3]);
		dm->debug_components &= (~ODM_COMP_API);
	}
}