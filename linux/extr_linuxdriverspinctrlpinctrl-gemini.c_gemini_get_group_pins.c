#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct gemini_pmx {scalar_t__ is_3516; scalar_t__ is_3512; scalar_t__ flash_pin; } ;
struct TYPE_4__ {unsigned int* pins; unsigned int num_pins; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {unsigned int* pins; unsigned int num_pins; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 TYPE_2__* gemini_3512_pin_groups ; 
 TYPE_1__* gemini_3516_pin_groups ; 
 unsigned int* pflash_3512_pins_extended ; 
 unsigned int* pflash_3516_pins_extended ; 
 struct gemini_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int gemini_get_group_pins(struct pinctrl_dev *pctldev,
				 unsigned int selector,
				 const unsigned int **pins,
				 unsigned int *num_pins)
{
	struct gemini_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	/* The special case with the 3516 flash pin */
	if (pmx->flash_pin &&
	    pmx->is_3512 &&
	    !strcmp(gemini_3512_pin_groups[selector].name, "pflashgrp")) {
		*pins = pflash_3512_pins_extended;
		*num_pins = ARRAY_SIZE(pflash_3512_pins_extended);
		return 0;
	}
	if (pmx->flash_pin &&
	    pmx->is_3516 &&
	    !strcmp(gemini_3516_pin_groups[selector].name, "pflashgrp")) {
		*pins = pflash_3516_pins_extended;
		*num_pins = ARRAY_SIZE(pflash_3516_pins_extended);
		return 0;
	}
	if (pmx->is_3512) {
		*pins = gemini_3512_pin_groups[selector].pins;
		*num_pins = gemini_3512_pin_groups[selector].num_pins;
	}
	if (pmx->is_3516) {
		*pins = gemini_3516_pin_groups[selector].pins;
		*num_pins = gemini_3516_pin_groups[selector].num_pins;
	}
	return 0;
}