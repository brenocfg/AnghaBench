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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 unsigned int ETH_TEST_FL_OFFLINE ; 
 int /*<<< orphan*/  ef4_mdio_an_reconfigure (struct ef4_nic*) ; 
 int tenxpress_special_reset (struct ef4_nic*) ; 

__attribute__((used)) static int
sfx7101_run_tests(struct ef4_nic *efx, int *results, unsigned flags)
{
	int rc;

	if (!(flags & ETH_TEST_FL_OFFLINE))
		return 0;

	/* BIST is automatically run after a special software reset */
	rc = tenxpress_special_reset(efx);
	results[0] = rc ? -1 : 1;

	ef4_mdio_an_reconfigure(efx);

	return rc;
}