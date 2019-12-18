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
struct dstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  core_module_paths ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct dstr*) ; 
 struct dstr* da_push_back_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char const*) ; 

void obs_add_data_path(const char *path)
{
	struct dstr *new_path = da_push_back_new(core_module_paths);
	dstr_init_copy(new_path, path);
	da_push_back(core_module_paths, new_path);
}