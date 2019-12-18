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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/ * obs_data_create_from_json_file (char const*) ; 
 scalar_t__ os_file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_rename (int /*<<< orphan*/ ,char const*) ; 

obs_data_t *obs_data_create_from_json_file_safe(const char *json_file,
						const char *backup_ext)
{
	obs_data_t *file_data = obs_data_create_from_json_file(json_file);
	if (!file_data && backup_ext && *backup_ext) {
		struct dstr backup_file = {0};

		dstr_copy(&backup_file, json_file);
		if (*backup_ext != '.')
			dstr_cat(&backup_file, ".");
		dstr_cat(&backup_file, backup_ext);

		if (os_file_exists(backup_file.array)) {
			blog(LOG_WARNING,
			     "obs-data.c: "
			     "[obs_data_create_from_json_file_safe] "
			     "attempting backup file");

			/* delete current file if corrupt to prevent it from
			 * being backed up again */
			os_rename(backup_file.array, json_file);

			file_data = obs_data_create_from_json_file(json_file);
		}

		dstr_free(&backup_file);
	}

	return file_data;
}