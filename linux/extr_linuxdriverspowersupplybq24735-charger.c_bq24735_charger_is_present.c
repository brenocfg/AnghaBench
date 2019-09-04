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
struct bq24735 {TYPE_1__* client; scalar_t__ status_gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24735_CHG_OPT ; 
 int BQ24735_CHG_OPT_AC_PRESENT ; 
 int bq24735_read_word (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpiod_get_value_cansleep (scalar_t__) ; 

__attribute__((used)) static bool bq24735_charger_is_present(struct bq24735 *charger)
{
	if (charger->status_gpio) {
		return !gpiod_get_value_cansleep(charger->status_gpio);
	} else {
		int ac = 0;

		ac = bq24735_read_word(charger->client, BQ24735_CHG_OPT);
		if (ac < 0) {
			dev_dbg(&charger->client->dev,
				"Failed to read charger options : %d\n",
				ac);
			return false;
		}
		return (ac & BQ24735_CHG_OPT_AC_PRESENT) ? true : false;
	}

	return false;
}