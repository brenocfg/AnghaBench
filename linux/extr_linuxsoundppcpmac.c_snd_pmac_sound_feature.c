#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pmac {int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* feature_call ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PMAC_FTR_SOUND_CHIP_ENABLE ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_pmac_sound_feature(struct snd_pmac *chip, int enable)
{
	if (ppc_md.feature_call)
		ppc_md.feature_call(PMAC_FTR_SOUND_CHIP_ENABLE, chip->node, 0, enable);
}