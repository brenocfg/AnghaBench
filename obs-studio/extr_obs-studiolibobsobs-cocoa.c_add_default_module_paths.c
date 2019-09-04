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
 int /*<<< orphan*/ * module_bin ; 
 int /*<<< orphan*/ * module_data ; 
 int module_patterns_size ; 
 int /*<<< orphan*/  obs_add_module_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void add_default_module_paths(void)
{
	for (int i = 0; i < module_patterns_size; i++)
		obs_add_module_path(module_bin[i], module_data[i]);
}