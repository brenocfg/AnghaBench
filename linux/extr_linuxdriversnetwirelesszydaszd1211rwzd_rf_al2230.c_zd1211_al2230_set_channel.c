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
struct zd_ioreq16 {int member_1; int /*<<< orphan*/  member_0; } ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16 const*) ; 
 int /*<<< orphan*/  RF_RV_BITS ; 
#define  ZD_CR138 129 
#define  ZD_CR203 128 
 int /*<<< orphan*/ ** zd1211_al2230_table ; 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16 const*,int /*<<< orphan*/ ) ; 
 struct zd_chip* zd_rf_to_chip (struct zd_rf*) ; 
 int zd_rfwritev_locked (struct zd_chip*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zd1211_al2230_set_channel(struct zd_rf *rf, u8 channel)
{
	int r;
	const u32 *rv = zd1211_al2230_table[channel-1];
	struct zd_chip *chip = zd_rf_to_chip(rf);
	static const struct zd_ioreq16 ioreqs[] = {
		{ ZD_CR138, 0x28 },
		{ ZD_CR203, 0x06 },
	};

	r = zd_rfwritev_locked(chip, rv, 3, RF_RV_BITS);
	if (r)
		return r;
	return zd_iowrite16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
}