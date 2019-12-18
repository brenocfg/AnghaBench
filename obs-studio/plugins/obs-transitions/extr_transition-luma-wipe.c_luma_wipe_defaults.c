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
 int /*<<< orphan*/  S_LUMA_IMG ; 
 int /*<<< orphan*/  S_LUMA_INV ; 
 int /*<<< orphan*/  S_LUMA_SOFT ; 
 int /*<<< orphan*/  obs_data_set_default_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_data_set_default_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  obs_data_set_default_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void luma_wipe_defaults(obs_data_t *settings)
{
	obs_data_set_default_string(settings, S_LUMA_IMG, "linear-h.png");
	obs_data_set_default_double(settings, S_LUMA_SOFT, 0.03);
	obs_data_set_default_bool(settings, S_LUMA_INV, false);
}