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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ SMC_ASCII_BLANK ; 
 int SMC_MAX_PNETID_LEN ; 

__attribute__((used)) static bool smc_pnet_match(u8 *pnetid1, u8 *pnetid2)
{
	int i;

	for (i = 0; i < SMC_MAX_PNETID_LEN; i++) {
		if ((pnetid1[i] == 0 || pnetid1[i] == SMC_ASCII_BLANK) &&
		    (pnetid2[i] == 0 || pnetid2[i] == SMC_ASCII_BLANK))
			break;
		if (pnetid1[i] != pnetid2[i])
			return false;
	}
	return true;
}