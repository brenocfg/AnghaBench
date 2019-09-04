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

/* Variables and functions */
 int FDT_ERR_NOTFOUND ; 
 int fdt_add_subnode_namelen (void*,int,char const*,int) ; 
 int fdt_subnode_offset_namelen (void*,int,char const*,int) ; 
 int /*<<< orphan*/  report_error (char const*,int,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int create_paths(void *blob, const char *in_path)
{
	const char *path = in_path;
	const char *sep;
	int node, offset = 0;

	/* skip leading '/' */
	while (*path == '/')
		path++;

	for (sep = path; *sep; path = sep + 1, offset = node) {
		/* equivalent to strchrnul(), but it requires _GNU_SOURCE */
		sep = strchr(path, '/');
		if (!sep)
			sep = path + strlen(path);

		node = fdt_subnode_offset_namelen(blob, offset, path,
				sep - path);
		if (node == -FDT_ERR_NOTFOUND) {
			node = fdt_add_subnode_namelen(blob, offset, path,
						       sep - path);
		}
		if (node < 0) {
			report_error(path, sep - path, node);
			return -1;
		}
	}

	return 0;
}