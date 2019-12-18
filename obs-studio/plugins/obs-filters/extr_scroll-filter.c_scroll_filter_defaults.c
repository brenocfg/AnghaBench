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
 int /*<<< orphan*/  obs_data_set_default_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void scroll_filter_defaults(obs_data_t *settings)
{
	obs_data_set_default_bool(settings, "limit_size", false);
	obs_data_set_default_int(settings, "cx", 100);
	obs_data_set_default_int(settings, "cy", 100);
	obs_data_set_default_bool(settings, "loop", true);
}