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
struct nvec_power {int /*<<< orphan*/  nvec; } ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
 char NVEC_BAT ; 
 char SLOT_STATUS ; 
 char* bat_init ; 
 int /*<<< orphan*/  nvec_write_async (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void get_bat_mfg_data(struct nvec_power *power)
{
	int i;
	char buf[] = { NVEC_BAT, SLOT_STATUS };

	for (i = 0; i < ARRAY_SIZE(bat_init); i++) {
		buf[1] = bat_init[i];
		nvec_write_async(power->nvec, buf, 2);
	}
}