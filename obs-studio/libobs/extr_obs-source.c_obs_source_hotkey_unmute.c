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
struct obs_source {int dummy; } ;
typedef  int /*<<< orphan*/  obs_hotkey_t ;
typedef  int /*<<< orphan*/ * obs_hotkey_pair_id ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_muted (struct obs_source*) ; 
 int /*<<< orphan*/  obs_source_set_muted (struct obs_source*,int) ; 

__attribute__((used)) static bool obs_source_hotkey_unmute(void *data, obs_hotkey_pair_id id,
				     obs_hotkey_t *key, bool pressed)
{
	UNUSED_PARAMETER(id);
	UNUSED_PARAMETER(key);

	struct obs_source *source = data;

	if (!pressed || !obs_source_muted(source))
		return false;

	obs_source_set_muted(source, false);
	return true;
}