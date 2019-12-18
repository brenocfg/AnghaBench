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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  SETTING_ANY_FULLSCREEN ; 
 int /*<<< orphan*/  SETTING_MODE ; 
 scalar_t__ obs_data_has_user_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool using_older_non_mode_format(obs_data_t *settings)
{
	return obs_data_has_user_value(settings, SETTING_ANY_FULLSCREEN) &&
	       !obs_data_has_user_value(settings, SETTING_MODE);
}