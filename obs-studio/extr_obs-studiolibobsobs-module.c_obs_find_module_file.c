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
struct dstr {char* array; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  data_path; } ;
typedef  TYPE_1__ obs_module_t ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_cat_ch (struct dstr*,char) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,int /*<<< orphan*/ ) ; 
 char dstr_end (struct dstr*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_is_empty (struct dstr*) ; 
 int /*<<< orphan*/  os_file_exists (char*) ; 

char *obs_find_module_file(obs_module_t *module, const char *file)
{
	struct dstr output = {0};

	if (!file)
		file = "";

	if (!module)
		return NULL;

	dstr_copy(&output, module->data_path);
	if (!dstr_is_empty(&output) && dstr_end(&output) != '/' && *file)
		dstr_cat_ch(&output, '/');
	dstr_cat(&output, file);

	if (!os_file_exists(output.array))
		dstr_free(&output);
	return output.array;
}