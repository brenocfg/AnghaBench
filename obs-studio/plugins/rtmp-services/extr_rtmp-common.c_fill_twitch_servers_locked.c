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
struct twitch_ingest {char* url; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_module_text (char*) ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct twitch_ingest twitch_ingest (size_t) ; 
 size_t twitch_ingest_count () ; 

__attribute__((used)) static bool fill_twitch_servers_locked(obs_property_t *servers_prop)
{
	size_t count = twitch_ingest_count();

	obs_property_list_add_string(servers_prop,
				     obs_module_text("Server.Auto"), "auto");

	if (count <= 1)
		return false;

	for (size_t i = 0; i < count; i++) {
		struct twitch_ingest ing = twitch_ingest(i);
		obs_property_list_add_string(servers_prop, ing.name, ing.url);
	}

	return true;
}