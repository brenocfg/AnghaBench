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
typedef  int /*<<< orphan*/  u8 ;
struct mt76x0_dev {TYPE_1__* ee; } ;
struct TYPE_2__ {int temp_off; } ;

/* Variables and functions */
 size_t MT_EE_TEMP_OFFSET ; 
 scalar_t__ field_valid (int /*<<< orphan*/ ) ; 
 int sign_extend (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt76x0_set_temp_offset(struct mt76x0_dev *dev, u8 *eeprom)
{
	u8 temp = eeprom[MT_EE_TEMP_OFFSET];

	if (field_valid(temp))
		dev->ee->temp_off = sign_extend(temp, 8);
	else
		dev->ee->temp_off = -10;
}