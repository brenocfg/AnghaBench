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
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 int fill_twitch_servers_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twitch_ingests_lock () ; 
 int /*<<< orphan*/  twitch_ingests_unlock () ; 

__attribute__((used)) static inline bool fill_twitch_servers(obs_property_t *servers_prop)
{
	bool success;

	twitch_ingests_lock();
	success = fill_twitch_servers_locked(servers_prop);
	twitch_ingests_unlock();

	return success;
}