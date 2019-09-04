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
struct nscookie {int dummy; } ;

/* Variables and functions */
 scalar_t__ PATH_MAX ; 
 int /*<<< orphan*/  R_OK ; 
 size_t __symbol__join_symfs (char*,scalar_t__,char*) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 char* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  nsinfo__mountns_enter (struct nsinfo*,struct nscookie*) ; 
 int /*<<< orphan*/  nsinfo__mountns_exit (struct nscookie*) ; 
 char* realpath (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,char const*,char const*) ; 
 int /*<<< orphan*/  zfree (char**) ; 

__attribute__((used)) static char *build_id_cache__find_debug(const char *sbuild_id,
					struct nsinfo *nsi)
{
	char *realname = NULL;
	char *debugfile;
	struct nscookie nsc;
	size_t len = 0;

	debugfile = calloc(1, PATH_MAX);
	if (!debugfile)
		goto out;

	len = __symbol__join_symfs(debugfile, PATH_MAX,
				   "/usr/lib/debug/.build-id/");
	snprintf(debugfile + len, PATH_MAX - len, "%.2s/%s.debug", sbuild_id,
		 sbuild_id + 2);

	nsinfo__mountns_enter(nsi, &nsc);
	realname = realpath(debugfile, NULL);
	if (realname && access(realname, R_OK))
		zfree(&realname);
	nsinfo__mountns_exit(&nsc);
out:
	free(debugfile);
	return realname;
}