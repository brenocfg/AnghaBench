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
struct zd_ioreq16 {int member_1; int /*<<< orphan*/  member_0; } ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16 const*) ; 
#define  ZD_CR10 129 
#define  ZD_CR11 128 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16 const*,int /*<<< orphan*/ ) ; 
 struct zd_chip* zd_rf_to_chip (struct zd_rf*) ; 

__attribute__((used)) static int rf2959_switch_radio_on(struct zd_rf *rf)
{
	static const struct zd_ioreq16 ioreqs[] = {
		{ ZD_CR10, 0x89 },
		{ ZD_CR11, 0x00 },
	};
	struct zd_chip *chip = zd_rf_to_chip(rf);

	return zd_iowrite16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
}