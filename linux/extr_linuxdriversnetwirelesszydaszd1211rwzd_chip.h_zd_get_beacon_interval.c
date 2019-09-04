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
typedef  int /*<<< orphan*/  u32 ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_BCN_INTERVAL ; 
 int zd_ioread32 (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int zd_get_beacon_interval(struct zd_chip *chip, u32 *interval)
{
	return zd_ioread32(chip, CR_BCN_INTERVAL, interval);
}