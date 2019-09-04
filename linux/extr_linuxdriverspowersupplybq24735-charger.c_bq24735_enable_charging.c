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
struct bq24735 {int /*<<< orphan*/  client; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ ext_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24735_CHG_OPT ; 
 int /*<<< orphan*/  BQ24735_CHG_OPT_CHARGE_DISABLE ; 
 int bq24735_config_charger (struct bq24735*) ; 
 int bq24735_update_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int bq24735_enable_charging(struct bq24735 *charger)
{
	int ret;

	if (charger->pdata->ext_control)
		return 0;

	ret = bq24735_config_charger(charger);
	if (ret)
		return ret;

	return bq24735_update_word(charger->client, BQ24735_CHG_OPT,
				   BQ24735_CHG_OPT_CHARGE_DISABLE, 0);
}