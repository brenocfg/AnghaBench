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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct cs35l36_private {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int CS35L36_FS1_DEFAULT_VAL ; 
 int CS35L36_FS1_WINDOW_MASK ; 
 int CS35L36_FS2_DEFAULT_VAL ; 
 int CS35L36_FS2_WINDOW_MASK ; 
 int CS35L36_FS2_WINDOW_SHIFT ; 
 unsigned int CS35L36_FS_NOM_6MHZ ; 
 int /*<<< orphan*/  CS35L36_TESTKEY_CTRL ; 
 int /*<<< orphan*/  CS35L36_TEST_LOCK1 ; 
 int /*<<< orphan*/  CS35L36_TEST_LOCK2 ; 
 int /*<<< orphan*/  CS35L36_TEST_UNLOCK1 ; 
 int /*<<< orphan*/  CS35L36_TEST_UNLOCK2 ; 
 int /*<<< orphan*/  CS35L36_TST_FS_MON0 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs35l36_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs35l36_dai_set_sysclk(struct snd_soc_dai *dai, int clk_id,
				  unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct cs35l36_private *cs35l36 =
			snd_soc_component_get_drvdata(component);
	int fs1, fs2;

	if (freq > CS35L36_FS_NOM_6MHZ) {
		fs1 = CS35L36_FS1_DEFAULT_VAL;
		fs2 = CS35L36_FS2_DEFAULT_VAL;
	} else {
		fs1 = 3 * ((CS35L36_FS_NOM_6MHZ * 4 + freq - 1) / freq) + 4;
		fs2 = 5 * ((CS35L36_FS_NOM_6MHZ * 4 + freq - 1) / freq) + 4;
	}

	regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			CS35L36_TEST_UNLOCK1);
	regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			CS35L36_TEST_UNLOCK2);

	regmap_update_bits(cs35l36->regmap, CS35L36_TST_FS_MON0,
			   CS35L36_FS1_WINDOW_MASK | CS35L36_FS2_WINDOW_MASK,
			   fs1 | (fs2 << CS35L36_FS2_WINDOW_SHIFT));

	regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			CS35L36_TEST_LOCK1);
	regmap_write(cs35l36->regmap, CS35L36_TESTKEY_CTRL,
			CS35L36_TEST_LOCK2);
	return 0;
}