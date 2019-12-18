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
 int /*<<< orphan*/  async_sync_test ; 
 int /*<<< orphan*/  buffering_async_sync_test ; 
 int /*<<< orphan*/  obs_register_source (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_audio ; 
 int /*<<< orphan*/  sync_video ; 
 int /*<<< orphan*/  test_filter ; 
 int /*<<< orphan*/  test_random ; 
 int /*<<< orphan*/  test_sinewave ; 

bool obs_module_load(void)
{
	obs_register_source(&test_random);
	obs_register_source(&test_sinewave);
	obs_register_source(&test_filter);
	obs_register_source(&async_sync_test);
	obs_register_source(&buffering_async_sync_test);
	obs_register_source(&sync_video);
	obs_register_source(&sync_audio);
	return true;
}