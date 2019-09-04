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
struct bios_rfkill2_state {int count; struct bios_rfkill2_device_state* device; } ;
struct bios_rfkill2_device_state {scalar_t__ rfkill_id; int /*<<< orphan*/  power; } ;
typedef  int /*<<< orphan*/  state ;
struct TYPE_2__ {int num; scalar_t__ id; int /*<<< orphan*/  rfkill; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPWMI_READ ; 
 int /*<<< orphan*/  HPWMI_WIRELESS2_QUERY ; 
 int /*<<< orphan*/  IS_HWBLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_SWBLOCKED (int /*<<< orphan*/ ) ; 
 int hp_wmi_perform_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bios_rfkill2_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 TYPE_1__* rfkill2 ; 
 int rfkill2_count ; 
 int /*<<< orphan*/  rfkill_set_states (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hp_wmi_rfkill2_refresh(void)
{
	struct bios_rfkill2_state state;
	int err, i;

	err = hp_wmi_perform_query(HPWMI_WIRELESS2_QUERY, HPWMI_READ, &state,
				   0, sizeof(state));
	if (err)
		return err;

	for (i = 0; i < rfkill2_count; i++) {
		int num = rfkill2[i].num;
		struct bios_rfkill2_device_state *devstate;
		devstate = &state.device[num];

		if (num >= state.count ||
		    devstate->rfkill_id != rfkill2[i].id) {
			pr_warn("power configuration of the wireless devices unexpectedly changed\n");
			continue;
		}

		rfkill_set_states(rfkill2[i].rfkill,
				  IS_SWBLOCKED(devstate->power),
				  IS_HWBLOCKED(devstate->power));
	}

	return 0;
}