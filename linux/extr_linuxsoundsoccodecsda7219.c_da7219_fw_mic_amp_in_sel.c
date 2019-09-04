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
struct device {int dummy; } ;
typedef  enum da7219_mic_amp_in_sel { ____Placeholder_da7219_mic_amp_in_sel } da7219_mic_amp_in_sel ;

/* Variables and functions */
 int DA7219_MIC_AMP_IN_SEL_DIFF ; 
 int DA7219_MIC_AMP_IN_SEL_SE_N ; 
 int DA7219_MIC_AMP_IN_SEL_SE_P ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum da7219_mic_amp_in_sel
	da7219_fw_mic_amp_in_sel(struct device *dev, const char *str)
{
	if (!strcmp(str, "diff")) {
		return DA7219_MIC_AMP_IN_SEL_DIFF;
	} else if (!strcmp(str, "se_p")) {
		return DA7219_MIC_AMP_IN_SEL_SE_P;
	} else if (!strcmp(str, "se_n")) {
		return DA7219_MIC_AMP_IN_SEL_SE_N;
	} else {
		dev_warn(dev, "Invalid mic input type selection");
		return DA7219_MIC_AMP_IN_SEL_DIFF;
	}
}