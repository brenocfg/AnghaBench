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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fwrite (void*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

void llvm__dump_obj(const char *path, void *obj_buf, size_t size)
{
	char *obj_path = strdup(path);
	FILE *fp;
	char *p;

	if (!obj_path) {
		pr_warning("WARNING: Not enough memory, skip object dumping\n");
		return;
	}

	p = strrchr(obj_path, '.');
	if (!p || (strcmp(p, ".c") != 0)) {
		pr_warning("WARNING: invalid llvm source path: '%s', skip object dumping\n",
			   obj_path);
		goto out;
	}

	p[1] = 'o';
	fp = fopen(obj_path, "wb");
	if (!fp) {
		pr_warning("WARNING: failed to open '%s': %s, skip object dumping\n",
			   obj_path, strerror(errno));
		goto out;
	}

	pr_info("LLVM: dumping %s\n", obj_path);
	if (fwrite(obj_buf, size, 1, fp) != 1)
		pr_warning("WARNING: failed to write to file '%s': %s, skip object dumping\n",
			   obj_path, strerror(errno));
	fclose(fp);
out:
	free(obj_path);
}