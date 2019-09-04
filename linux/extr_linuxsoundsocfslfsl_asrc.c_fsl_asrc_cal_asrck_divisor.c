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
struct fsl_asrc_pair {int dummy; } ;

/* Variables and functions */
 int ASRCDRi_AxCPi_WIDTH ; 

__attribute__((used)) static u32 fsl_asrc_cal_asrck_divisor(struct fsl_asrc_pair *pair, u32 div)
{
	u32 ps;

	/* Calculate the divisors: prescaler [2^0, 2^7], divder [1, 8] */
	for (ps = 0; div > 8; ps++)
		div >>= 1;

	return ((div - 1) << ASRCDRi_AxCPi_WIDTH) | ps;
}