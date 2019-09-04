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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct zd_rf {int dummy; } ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_RV_BITS ; 
 int /*<<< orphan*/ ** rf2959_table ; 
 struct zd_chip* zd_rf_to_chip (struct zd_rf*) ; 
 int zd_rfwrite_locked (struct zd_chip*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rf2959_set_channel(struct zd_rf *rf, u8 channel)
{
	int i, r;
	const u32 *rv = rf2959_table[channel-1];
	struct zd_chip *chip = zd_rf_to_chip(rf);

	for (i = 0; i < 2; i++) {
		r = zd_rfwrite_locked(chip, rv[i], RF_RV_BITS);
		if (r)
			return r;
	}
	return 0;
}