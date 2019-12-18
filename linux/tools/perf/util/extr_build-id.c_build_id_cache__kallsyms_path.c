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
 char* DSO__NAME_KALLSYMS ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 char* buildid_dir ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*,char const*) ; 

char *build_id_cache__kallsyms_path(const char *sbuild_id, char *bf,
				    size_t size)
{
	bool retry_old = true;

	snprintf(bf, size, "%s/%s/%s/kallsyms",
		 buildid_dir, DSO__NAME_KALLSYMS, sbuild_id);
retry:
	if (!access(bf, F_OK))
		return bf;
	if (retry_old) {
		/* Try old style kallsyms cache */
		snprintf(bf, size, "%s/%s/%s",
			 buildid_dir, DSO__NAME_KALLSYMS, sbuild_id);
		retry_old = false;
		goto retry;
	}

	return NULL;
}