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
 int /*<<< orphan*/  SETTING_LUMA_MAX ; 
 int /*<<< orphan*/  SETTING_LUMA_MAX_SMOOTH ; 
 int /*<<< orphan*/  SETTING_LUMA_MIN ; 
 int /*<<< orphan*/  SETTING_LUMA_MIN_SMOOTH ; 
 int /*<<< orphan*/  obs_data_set_default_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 

__attribute__((used)) static void luma_key_defaults(obs_data_t *settings)
{
	obs_data_set_default_double(settings, SETTING_LUMA_MAX, 1.0);
	obs_data_set_default_double(settings, SETTING_LUMA_MIN, 0.0);
	obs_data_set_default_double(settings, SETTING_LUMA_MAX_SMOOTH, 0.0);
	obs_data_set_default_double(settings, SETTING_LUMA_MIN_SMOOTH, 0.0);
}