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
typedef  scalar_t__ ut8 ;
struct TYPE_2__ {scalar_t__ number; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int RAsmLm32RegNumber ; 
 TYPE_1__* RAsmLm32Regs ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_number_to_string(ut8 reg, char *str) {
	ut8 match_idx = 0xff;
	int i;
	for (i = 0; i < RAsmLm32RegNumber; i++) {
		if (RAsmLm32Regs[i].number == reg) {
			match_idx = i;
			break;
		}
	}
	//register number not found in array. this shouldn't happen
	if (match_idx == 0xff) {
		return -1;
	}
	strcpy (str, RAsmLm32Regs[match_idx].name);
	return 0;
}