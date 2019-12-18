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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int PATH_MAX ; 
 char* build_id_cache__linkname (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t readlink (char*,char*,int) ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 

char *build_id_cache__origname(const char *sbuild_id)
{
	char *linkname;
	char buf[PATH_MAX];
	char *ret = NULL, *p;
	size_t offs = 5;	/* == strlen("../..") */
	ssize_t len;

	linkname = build_id_cache__linkname(sbuild_id, NULL, 0);
	if (!linkname)
		return NULL;

	len = readlink(linkname, buf, sizeof(buf) - 1);
	if (len <= 0)
		goto out;
	buf[len] = '\0';

	/* The link should be "../..<origpath>/<sbuild_id>" */
	p = strrchr(buf, '/');	/* Cut off the "/<sbuild_id>" */
	if (p && (p > buf + offs)) {
		*p = '\0';
		if (buf[offs + 1] == '[')
			offs++;	/*
				 * This is a DSO name, like [kernel.kallsyms].
				 * Skip the first '/', since this is not the
				 * cache of a regular file.
				 */
		ret = strdup(buf + offs);	/* Skip "../..[/]" */
	}
out:
	free(linkname);
	return ret;
}