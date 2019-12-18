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
typedef  int /*<<< orphan*/  u64 ;
struct dirent {char* d_name; scalar_t__ d_type; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  options ;
typedef  int /*<<< orphan*/  abs_path ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_REG ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  free_popup_options (char**,int) ; 
 char* getenv (char*) ; 
 char* input_name ; 
 int is_input_name_malloced ; 
 scalar_t__ is_perf_magic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 char* strdup (char*) ; 
 int ui__popup_menu (int,char**) ; 
 int /*<<< orphan*/  ui__warning (char*) ; 
 int /*<<< orphan*/  zfree (char**) ; 

__attribute__((used)) static int switch_data_file(void)
{
	char *pwd, *options[32], *abs_path[32], *tmp;
	DIR *pwd_dir;
	int nr_options = 0, choice = -1, ret = -1;
	struct dirent *dent;

	pwd = getenv("PWD");
	if (!pwd)
		return ret;

	pwd_dir = opendir(pwd);
	if (!pwd_dir)
		return ret;

	memset(options, 0, sizeof(options));
	memset(abs_path, 0, sizeof(abs_path));

	while ((dent = readdir(pwd_dir))) {
		char path[PATH_MAX];
		u64 magic;
		char *name = dent->d_name;
		FILE *file;

		if (!(dent->d_type == DT_REG))
			continue;

		snprintf(path, sizeof(path), "%s/%s", pwd, name);

		file = fopen(path, "r");
		if (!file)
			continue;

		if (fread(&magic, 1, 8, file) < 8)
			goto close_file_and_continue;

		if (is_perf_magic(magic)) {
			options[nr_options] = strdup(name);
			if (!options[nr_options])
				goto close_file_and_continue;

			abs_path[nr_options] = strdup(path);
			if (!abs_path[nr_options]) {
				zfree(&options[nr_options]);
				ui__warning("Can't search all data files due to memory shortage.\n");
				fclose(file);
				break;
			}

			nr_options++;
		}

close_file_and_continue:
		fclose(file);
		if (nr_options >= 32) {
			ui__warning("Too many perf data files in PWD!\n"
				    "Only the first 32 files will be listed.\n");
			break;
		}
	}
	closedir(pwd_dir);

	if (nr_options) {
		choice = ui__popup_menu(nr_options, options);
		if (choice < nr_options && choice >= 0) {
			tmp = strdup(abs_path[choice]);
			if (tmp) {
				if (is_input_name_malloced)
					free((void *)input_name);
				input_name = tmp;
				is_input_name_malloced = true;
				ret = 0;
			} else
				ui__warning("Data switch failed due to memory shortage!\n");
		}
	}

	free_popup_options(options, nr_options);
	free_popup_options(abs_path, nr_options);
	return ret;
}