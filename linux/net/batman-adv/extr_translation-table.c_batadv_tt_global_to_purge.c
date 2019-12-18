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
struct TYPE_2__ {int flags; int /*<<< orphan*/  added_at; } ;
struct batadv_tt_global_entry {TYPE_1__ common; int /*<<< orphan*/  roam_at; } ;

/* Variables and functions */
 int BATADV_TT_CLIENT_ROAM ; 
 unsigned long BATADV_TT_CLIENT_ROAM_TIMEOUT ; 
 int BATADV_TT_CLIENT_TEMP ; 
 unsigned long BATADV_TT_CLIENT_TEMP_TIMEOUT ; 
 scalar_t__ batadv_has_timed_out (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static bool batadv_tt_global_to_purge(struct batadv_tt_global_entry *tt_global,
				      char **msg)
{
	bool purge = false;
	unsigned long roam_timeout = BATADV_TT_CLIENT_ROAM_TIMEOUT;
	unsigned long temp_timeout = BATADV_TT_CLIENT_TEMP_TIMEOUT;

	if ((tt_global->common.flags & BATADV_TT_CLIENT_ROAM) &&
	    batadv_has_timed_out(tt_global->roam_at, roam_timeout)) {
		purge = true;
		*msg = "Roaming timeout\n";
	}

	if ((tt_global->common.flags & BATADV_TT_CLIENT_TEMP) &&
	    batadv_has_timed_out(tt_global->common.added_at, temp_timeout)) {
		purge = true;
		*msg = "Temporary client timeout\n";
	}

	return purge;
}