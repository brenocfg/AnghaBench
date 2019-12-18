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
struct mtk_base_afe {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MT8183_DAI_I2S_0 ; 
 int MT8183_DAI_I2S_1 ; 
 int MT8183_DAI_I2S_2 ; 
 int MT8183_DAI_I2S_3 ; 
 int MT8183_DAI_I2S_5 ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int get_i2s_id_by_name(struct mtk_base_afe *afe,
			      const char *name)
{
	if (strncmp(name, "I2S0", 4) == 0)
		return MT8183_DAI_I2S_0;
	else if (strncmp(name, "I2S1", 4) == 0)
		return MT8183_DAI_I2S_1;
	else if (strncmp(name, "I2S2", 4) == 0)
		return MT8183_DAI_I2S_2;
	else if (strncmp(name, "I2S3", 4) == 0)
		return MT8183_DAI_I2S_3;
	else if (strncmp(name, "I2S5", 4) == 0)
		return MT8183_DAI_I2S_5;
	else
		return -EINVAL;
}