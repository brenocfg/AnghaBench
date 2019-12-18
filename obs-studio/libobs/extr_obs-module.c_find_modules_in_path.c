#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct obs_module_path {int /*<<< orphan*/  bin; } ;
struct dstr {int array; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {size_t gl_pathc; TYPE_1__* gl_pathv; } ;
typedef  TYPE_2__ os_glob_t ;
typedef  int /*<<< orphan*/  obs_find_module_callback_t ;
struct TYPE_5__ {int directory; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_cat_ch (struct dstr*,char) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,int /*<<< orphan*/ ) ; 
 char dstr_end (struct dstr*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_is_empty (struct dstr*) ; 
 int /*<<< orphan*/  dstr_resize (struct dstr*,char*) ; 
 int /*<<< orphan*/  get_module_extension () ; 
 scalar_t__ os_glob (int,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  os_globfree (TYPE_2__*) ; 
 int /*<<< orphan*/  process_found_module (struct obs_module_path*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 char* strstr (int,char*) ; 

__attribute__((used)) static void find_modules_in_path(struct obs_module_path *omp,
				 obs_find_module_callback_t callback,
				 void *param)
{
	struct dstr search_path = {0};
	char *module_start;
	bool search_directories = false;
	os_glob_t *gi;

	dstr_copy(&search_path, omp->bin);

	module_start = strstr(search_path.array, "%module%");
	if (module_start) {
		dstr_resize(&search_path, module_start - search_path.array);
		search_directories = true;
	}

	if (!dstr_is_empty(&search_path) && dstr_end(&search_path) != '/')
		dstr_cat_ch(&search_path, '/');

	dstr_cat_ch(&search_path, '*');
	if (!search_directories)
		dstr_cat(&search_path, get_module_extension());

	if (os_glob(search_path.array, 0, &gi) == 0) {
		for (size_t i = 0; i < gi->gl_pathc; i++) {
			if (search_directories == gi->gl_pathv[i].directory)
				process_found_module(omp, gi->gl_pathv[i].path,
						     search_directories,
						     callback, param);
		}

		os_globfree(gi);
	}

	dstr_free(&search_path);
}