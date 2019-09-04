#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dstr {char* array; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {char const* mod_name; } ;
typedef  TYPE_1__ obs_module_t ;
struct TYPE_5__ {int /*<<< orphan*/  module_config_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_cat_ch (struct dstr*,char) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,int /*<<< orphan*/ ) ; 
 char dstr_end (struct dstr*) ; 
 int /*<<< orphan*/  dstr_is_empty (struct dstr*) ; 
 TYPE_3__* obs ; 

char *obs_module_get_config_path(obs_module_t *module, const char *file)
{
	struct dstr output = {0};

	dstr_copy(&output, obs->module_config_path);
	if (!dstr_is_empty(&output) && dstr_end(&output) != '/')
		dstr_cat_ch(&output, '/');
	dstr_cat(&output, module->mod_name);
	dstr_cat_ch(&output, '/');
	dstr_cat(&output, file);

	return output.array;
}