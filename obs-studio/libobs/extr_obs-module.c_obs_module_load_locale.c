#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ obs_module_t ;
typedef  int /*<<< orphan*/  lookup_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ astrcmpi (char const*,char const*) ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 char* obs_find_module_file (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_lookup_add (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * text_lookup_create (char*) ; 

lookup_t *obs_module_load_locale(obs_module_t *module,
				 const char *default_locale, const char *locale)
{
	struct dstr str = {0};
	lookup_t *lookup = NULL;

	if (!module || !default_locale || !locale) {
		blog(LOG_WARNING, "obs_module_load_locale: Invalid parameters");
		return NULL;
	}

	dstr_copy(&str, "locale/");
	dstr_cat(&str, default_locale);
	dstr_cat(&str, ".ini");

	char *file = obs_find_module_file(module, str.array);
	if (file)
		lookup = text_lookup_create(file);

	bfree(file);

	if (!lookup) {
		blog(LOG_WARNING, "Failed to load '%s' text for module: '%s'",
		     default_locale, module->file);
		goto cleanup;
	}

	if (astrcmpi(locale, default_locale) == 0)
		goto cleanup;

	dstr_copy(&str, "/locale/");
	dstr_cat(&str, locale);
	dstr_cat(&str, ".ini");

	file = obs_find_module_file(module, str.array);

	if (!text_lookup_add(lookup, file))
		blog(LOG_WARNING, "Failed to load '%s' text for module: '%s'",
		     locale, module->file);

	bfree(file);
cleanup:
	dstr_free(&str);
	return lookup;
}