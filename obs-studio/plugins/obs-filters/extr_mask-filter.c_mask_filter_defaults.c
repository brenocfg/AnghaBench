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
 int /*<<< orphan*/  SETTING_COLOR ; 
 int /*<<< orphan*/  SETTING_OPACITY ; 
 int /*<<< orphan*/  SETTING_TYPE ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_data_set_default_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mask_filter_defaults(obs_data_t *settings)
{
	obs_data_set_default_string(settings, SETTING_TYPE,
				    "mask_color_filter.effect");
	obs_data_set_default_int(settings, SETTING_COLOR, 0xFFFFFF);
	obs_data_set_default_int(settings, SETTING_OPACITY, 100);
}