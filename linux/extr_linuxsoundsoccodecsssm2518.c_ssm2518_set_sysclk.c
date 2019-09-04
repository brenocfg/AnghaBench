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
struct ssm2518 {unsigned int sysclk; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * constraints; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SSM2518_POWER1_NO_BCLK ; 
 int /*<<< orphan*/  SSM2518_REG_POWER1 ; 
 int SSM2518_SYSCLK ; 
#define  SSM2518_SYSCLK_SRC_BCLK 129 
#define  SSM2518_SYSCLK_SRC_MCLK 128 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct ssm2518* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  ssm2518_constraints_12288000 ; 
 int /*<<< orphan*/  ssm2518_constraints_2048000 ; 
 int /*<<< orphan*/  ssm2518_constraints_2822000 ; 
 int /*<<< orphan*/  ssm2518_constraints_3072000 ; 

__attribute__((used)) static int ssm2518_set_sysclk(struct snd_soc_component *component, int clk_id,
	int source, unsigned int freq, int dir)
{
	struct ssm2518 *ssm2518 = snd_soc_component_get_drvdata(component);
	unsigned int val;

	if (clk_id != SSM2518_SYSCLK)
		return -EINVAL;

	switch (source) {
	case SSM2518_SYSCLK_SRC_MCLK:
		val = 0;
		break;
	case SSM2518_SYSCLK_SRC_BCLK:
		/* In this case the bitclock is used as the system clock, and
		 * the bitclock signal needs to be connected to the MCLK pin and
		 * the BCLK pin is left unconnected */
		val = SSM2518_POWER1_NO_BCLK;
		break;
	default:
		return -EINVAL;
	}

	switch (freq) {
	case 0:
		ssm2518->constraints = NULL;
		break;
	case 2048000:
	case 4096000:
	case 8192000:
	case 3200000:
	case 6400000:
	case 12800000:
		ssm2518->constraints = &ssm2518_constraints_2048000;
		break;
	case 2822000:
	case 5644800:
	case 11289600:
	case 16934400:
	case 22579200:
	case 33868800:
	case 4410000:
	case 8820000:
	case 17640000:
		ssm2518->constraints = &ssm2518_constraints_2822000;
		break;
	case 3072000:
	case 6144000:
	case 38864000:
	case 4800000:
	case 9600000:
	case 19200000:
		ssm2518->constraints = &ssm2518_constraints_3072000;
		break;
	case 12288000:
	case 16384000:
	case 24576000:
		ssm2518->constraints = &ssm2518_constraints_12288000;
		break;
	default:
		return -EINVAL;
	}

	ssm2518->sysclk = freq;

	return regmap_update_bits(ssm2518->regmap, SSM2518_REG_POWER1,
			SSM2518_POWER1_NO_BCLK, val);
}