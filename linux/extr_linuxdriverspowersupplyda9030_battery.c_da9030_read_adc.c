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
typedef  int /*<<< orphan*/  uint8_t ;
struct da9030_charger {int /*<<< orphan*/  master; } ;
struct da9030_adc_res {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9030_VBAT_RES ; 
 int /*<<< orphan*/  da903x_reads (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void da9030_read_adc(struct da9030_charger *charger,
				   struct da9030_adc_res *adc)
{
	da903x_reads(charger->master, DA9030_VBAT_RES,
		     sizeof(*adc), (uint8_t *)adc);
}