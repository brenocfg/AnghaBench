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
typedef  int /*<<< orphan*/  u8 ;
struct zd_ioreq16 {int member_1; int /*<<< orphan*/  const member_0; } ;
struct zd_chip {int /*<<< orphan*/  rf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16 const*) ; 
#define  ZD_CR69 128 
 int update_ofdm_cal (struct zd_chip*,int /*<<< orphan*/ ) ; 
 int update_pwr_cal (struct zd_chip*,int /*<<< orphan*/ ) ; 
 int update_pwr_int (struct zd_chip*,int /*<<< orphan*/ ) ; 
 scalar_t__ zd_chip_is_zd1211b (struct zd_chip*) ; 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16 const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_rf_should_update_pwr_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_channel_integration_and_calibration(struct zd_chip *chip,
	                                              u8 channel)
{
	int r;

	if (!zd_rf_should_update_pwr_int(&chip->rf))
		return 0;

	r = update_pwr_int(chip, channel);
	if (r)
		return r;
	if (zd_chip_is_zd1211b(chip)) {
		static const struct zd_ioreq16 ioreqs[] = {
			{ ZD_CR69, 0x28 },
			{},
			{ ZD_CR69, 0x2a },
		};

		r = update_ofdm_cal(chip, channel);
		if (r)
			return r;
		r = update_pwr_cal(chip, channel);
		if (r)
			return r;
		r = zd_iowrite16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
		if (r)
			return r;
	}

	return 0;
}