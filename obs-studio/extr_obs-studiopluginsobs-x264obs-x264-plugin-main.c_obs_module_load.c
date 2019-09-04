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
 int /*<<< orphan*/  obs_register_encoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_x264_encoder ; 

bool obs_module_load(void)
{
	obs_register_encoder(&obs_x264_encoder);
	return true;
}