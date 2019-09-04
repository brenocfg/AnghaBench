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
struct zd_rf {int dummy; } ;
struct zd_ioreq16 {int member_1; int value; int /*<<< orphan*/  member_0; } ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16*) ; 
 int /*<<< orphan*/  RF_RV_BITS ; 
 int /*<<< orphan*/  UW2453_REGWRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZD_CR11 ; 
 int /*<<< orphan*/  ZD_CR251 ; 
 scalar_t__ zd_chip_is_zd1211b (struct zd_chip*) ; 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16*,int /*<<< orphan*/ ) ; 
 struct zd_chip* zd_rf_to_chip (struct zd_rf*) ; 
 int zd_rfwrite_locked (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uw2453_switch_radio_on(struct zd_rf *rf)
{
	int r;
	struct zd_chip *chip = zd_rf_to_chip(rf);
	struct zd_ioreq16 ioreqs[] = {
		{ ZD_CR11,  0x00 }, { ZD_CR251, 0x3f },
	};

	/* enter RXTX mode */
	r = zd_rfwrite_locked(chip, UW2453_REGWRITE(0, 0x25f94), RF_RV_BITS);
	if (r)
		return r;

	if (zd_chip_is_zd1211b(chip))
		ioreqs[1].value = 0x7f;

	return zd_iowrite16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
}