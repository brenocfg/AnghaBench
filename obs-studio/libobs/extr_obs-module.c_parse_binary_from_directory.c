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
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_cat_ch (struct dstr*,char) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_copy_dstr (struct dstr*,struct dstr*) ; 
 char dstr_end (struct dstr*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char const*) ; 
 char const* get_module_extension () ; 
 int /*<<< orphan*/  os_file_exists (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool parse_binary_from_directory(struct dstr *parsed_bin_path,
					const char *bin_path, const char *file)
{
	struct dstr directory = {0};
	bool found = true;

	dstr_copy(&directory, bin_path);
	dstr_replace(&directory, "%module%", file);
	if (dstr_end(&directory) != '/')
		dstr_cat_ch(&directory, '/');

	dstr_copy_dstr(parsed_bin_path, &directory);
	dstr_cat(parsed_bin_path, file);
	dstr_cat(parsed_bin_path, get_module_extension());

	if (!os_file_exists(parsed_bin_path->array)) {
		/* if the file doesn't exist, check with 'lib' prefix */
		dstr_copy_dstr(parsed_bin_path, &directory);
		dstr_cat(parsed_bin_path, "lib");
		dstr_cat(parsed_bin_path, file);
		dstr_cat(parsed_bin_path, get_module_extension());

		/* if neither exist, don't include this as a library */
		if (!os_file_exists(parsed_bin_path->array)) {
			dstr_free(parsed_bin_path);
			found = false;
		}
	}

	dstr_free(&directory);
	return found;
}