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
struct nsinfo {int dummy; } ;

/* Variables and functions */
 char* DSO__NAME_VDSO ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  buildid_dir ; 
 int /*<<< orphan*/  free (char*) ; 
 char* nsinfo__realpath (char const*,struct nsinfo*) ; 

char *build_id_cache__cachedir(const char *sbuild_id, const char *name,
			       struct nsinfo *nsi, bool is_kallsyms,
			       bool is_vdso)
{
	char *realname = (char *)name, *filename;
	bool slash = is_kallsyms || is_vdso;

	if (!slash) {
		realname = nsinfo__realpath(name, nsi);
		if (!realname)
			return NULL;
	}

	if (asprintf(&filename, "%s%s%s%s%s", buildid_dir, slash ? "/" : "",
		     is_vdso ? DSO__NAME_VDSO : realname,
		     sbuild_id ? "/" : "", sbuild_id ?: "") < 0)
		filename = NULL;

	if (!slash)
		free(realname);

	return filename;
}