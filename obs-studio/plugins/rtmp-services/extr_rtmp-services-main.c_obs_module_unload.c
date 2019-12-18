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

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_name ; 
 int /*<<< orphan*/  unload_twitch_data () ; 
 int /*<<< orphan*/  update_info ; 
 int /*<<< orphan*/  update_info_destroy (int /*<<< orphan*/ ) ; 

void obs_module_unload(void)
{
	update_info_destroy(update_info);
	unload_twitch_data();
	dstr_free(&module_name);
}