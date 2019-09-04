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
struct ccx_info {int /*<<< orphan*/ * NHM_result; int /*<<< orphan*/  echo_IGI; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static inline void phydm_print_nhm_result(char *output, u32 used, u32 out_len,
					  struct ccx_info *ccx_info)
{
	int i;

	for (i = 0; i <= 11; i++) {
		if (i == 5)
			PHYDM_SNPRINTF(
				output + used, out_len - used,
				"\r\n nhm_result[%d] = %d, echo_IGI = 0x%x", i,
				ccx_info->NHM_result[i], ccx_info->echo_IGI);
		else if (i == 11)
			PHYDM_SNPRINTF(output + used, out_len - used,
				       "\r\n nhm_result[%d] = %d\n", i,
				       ccx_info->NHM_result[i]);
		else
			PHYDM_SNPRINTF(output + used, out_len - used,
				       "\r\n nhm_result[%d] = %d", i,
				       ccx_info->NHM_result[i]);
	}
}