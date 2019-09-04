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
struct pcf85363 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int ALRM_DAY_A1E ; 
 unsigned int ALRM_HR_A1E ; 
 unsigned int ALRM_MIN_A1E ; 
 unsigned int ALRM_MON_A1E ; 
 unsigned int ALRM_SEC_A1E ; 
 int /*<<< orphan*/  CTRL_FLAGS ; 
 int /*<<< orphan*/  CTRL_INTA_EN ; 
 int /*<<< orphan*/  DT_ALARM_EN ; 
 unsigned int FLAGS_A1F ; 
 unsigned int INT_A1IE ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int _pcf85363_rtc_alarm_irq_enable(struct pcf85363 *pcf85363, unsigned
					  int enabled)
{
	unsigned int alarm_flags = ALRM_SEC_A1E | ALRM_MIN_A1E | ALRM_HR_A1E |
				   ALRM_DAY_A1E | ALRM_MON_A1E;
	int ret;

	ret = regmap_update_bits(pcf85363->regmap, DT_ALARM_EN, alarm_flags,
				 enabled ? alarm_flags : 0);
	if (ret)
		return ret;

	ret = regmap_update_bits(pcf85363->regmap, CTRL_INTA_EN,
				 INT_A1IE, enabled ? INT_A1IE : 0);

	if (ret || enabled)
		return ret;

	/* clear current flags */
	return regmap_update_bits(pcf85363->regmap, CTRL_FLAGS, FLAGS_A1F, 0);
}