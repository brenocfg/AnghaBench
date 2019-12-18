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
typedef  unsigned long long uint64_t ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FORMAT_SCAN_ELEMENTS_DIR ; 
 int /*<<< orphan*/  FORMAT_TYPE_FILE ; 
 int asprintf (char**,char*,char const*,...) ; 
 int closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,char*,char*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

int iioutils_get_type(unsigned *is_signed, unsigned *bytes, unsigned *bits_used,
		      unsigned *shift, uint64_t *mask, unsigned *be,
		      const char *device_dir, const char *name,
		      const char *generic_name)
{
	FILE *sysfsfp;
	int ret;
	DIR *dp;
	char *scan_el_dir, *builtname, *builtname_generic, *filename = 0;
	char signchar, endianchar;
	unsigned padint;
	const struct dirent *ent;

	ret = asprintf(&scan_el_dir, FORMAT_SCAN_ELEMENTS_DIR, device_dir);
	if (ret < 0)
		return -ENOMEM;

	ret = asprintf(&builtname, FORMAT_TYPE_FILE, name);
	if (ret < 0) {
		ret = -ENOMEM;
		goto error_free_scan_el_dir;
	}
	ret = asprintf(&builtname_generic, FORMAT_TYPE_FILE, generic_name);
	if (ret < 0) {
		ret = -ENOMEM;
		goto error_free_builtname;
	}

	dp = opendir(scan_el_dir);
	if (!dp) {
		ret = -errno;
		goto error_free_builtname_generic;
	}

	ret = -ENOENT;
	while (ent = readdir(dp), ent)
		if ((strcmp(builtname, ent->d_name) == 0) ||
		    (strcmp(builtname_generic, ent->d_name) == 0)) {
			ret = asprintf(&filename,
				       "%s/%s", scan_el_dir, ent->d_name);
			if (ret < 0) {
				ret = -ENOMEM;
				goto error_closedir;
			}

			sysfsfp = fopen(filename, "r");
			if (!sysfsfp) {
				ret = -errno;
				fprintf(stderr, "failed to open %s\n",
					filename);
				goto error_free_filename;
			}

			ret = fscanf(sysfsfp,
				     "%ce:%c%u/%u>>%u",
				     &endianchar,
				     &signchar,
				     bits_used,
				     &padint, shift);
			if (ret < 0) {
				ret = -errno;
				fprintf(stderr,
					"failed to pass scan type description\n");
				goto error_close_sysfsfp;
			} else if (ret != 5) {
				ret = -EIO;
				fprintf(stderr,
					"scan type description didn't match\n");
				goto error_close_sysfsfp;
			}

			*be = (endianchar == 'b');
			*bytes = padint / 8;
			if (*bits_used == 64)
				*mask = ~(0ULL);
			else
				*mask = (1ULL << *bits_used) - 1ULL;

			*is_signed = (signchar == 's');
			if (fclose(sysfsfp)) {
				ret = -errno;
				fprintf(stderr, "Failed to close %s\n",
					filename);
				goto error_free_filename;
			}

			sysfsfp = 0;
			free(filename);
			filename = 0;

			/*
			 * Avoid having a more generic entry overwriting
			 * the settings.
			 */
			if (strcmp(builtname, ent->d_name) == 0)
				break;
		}

error_close_sysfsfp:
	if (sysfsfp)
		if (fclose(sysfsfp))
			perror("iioutils_get_type(): Failed to close file");

error_free_filename:
	if (filename)
		free(filename);

error_closedir:
	if (closedir(dp) == -1)
		perror("iioutils_get_type(): Failed to close directory");

error_free_builtname_generic:
	free(builtname_generic);
error_free_builtname:
	free(builtname);
error_free_scan_el_dir:
	free(scan_el_dir);

	return ret;
}