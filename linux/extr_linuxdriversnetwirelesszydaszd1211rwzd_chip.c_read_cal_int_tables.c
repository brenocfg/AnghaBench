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
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int read_ofdm_cal_values (struct zd_chip*) ; 
 int read_pwr_cal_values (struct zd_chip*) ; 
 int read_pwr_int_values (struct zd_chip*) ; 

__attribute__((used)) static int read_cal_int_tables(struct zd_chip *chip)
{
	int r;

	r = read_pwr_cal_values(chip);
	if (r)
		return r;
	r = read_pwr_int_values(chip);
	if (r)
		return r;
	r = read_ofdm_cal_values(chip);
	if (r)
		return r;
	return 0;
}