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
typedef  int /*<<< orphan*/  u16 ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_BASIC_RATE_TBL ; 
 int zd_ioread16 (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int zd_chip_get_basic_rates(struct zd_chip *chip, u16 *cr_rates)
{
	return zd_ioread16(chip, CR_BASIC_RATE_TBL, cr_rates);
}