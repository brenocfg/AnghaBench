#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* bin_path; } ;
typedef  TYPE_1__ obs_module_t ;

/* Variables and functions */

const char *obs_get_module_binary_path(obs_module_t *module)
{
	return module ? module->bin_path : NULL;
}