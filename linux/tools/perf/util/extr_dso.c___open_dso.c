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
struct machine {char* root_dir; } ;
struct dso {int load_errno; int /*<<< orphan*/  binary_type; } ;
typedef  int /*<<< orphan*/  newpath ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int KMOD_DECOMP_LEN ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int do_open (char*) ; 
 scalar_t__ dso__decompress_kmodule_path (struct dso*,char*,char*,size_t) ; 
 scalar_t__ dso__needs_decompress (struct dso*) ; 
 scalar_t__ dso__read_binary_type_filename (struct dso*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_regular_file (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int __open_dso(struct dso *dso, struct machine *machine)
{
	int fd = -EINVAL;
	char *root_dir = (char *)"";
	char *name = malloc(PATH_MAX);
	bool decomp = false;

	if (!name)
		return -ENOMEM;

	if (machine)
		root_dir = machine->root_dir;

	if (dso__read_binary_type_filename(dso, dso->binary_type,
					    root_dir, name, PATH_MAX))
		goto out;

	if (!is_regular_file(name))
		goto out;

	if (dso__needs_decompress(dso)) {
		char newpath[KMOD_DECOMP_LEN];
		size_t len = sizeof(newpath);

		if (dso__decompress_kmodule_path(dso, name, newpath, len) < 0) {
			fd = -dso->load_errno;
			goto out;
		}

		decomp = true;
		strcpy(name, newpath);
	}

	fd = do_open(name);

	if (decomp)
		unlink(name);

out:
	free(name);
	return fd;
}