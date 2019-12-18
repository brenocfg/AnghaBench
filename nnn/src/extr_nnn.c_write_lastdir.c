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
 int /*<<< orphan*/  DPRINTF_S (scalar_t__) ; 
 int FALSE ; 
 int TRUE ; 
 scalar_t__ cfgdir ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (scalar_t__,char*) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 size_t strlen (scalar_t__) ; 
 int /*<<< orphan*/  xstrlcpy (scalar_t__,char*,int) ; 

__attribute__((used)) static bool write_lastdir(const char *curpath)
{
	bool ret = TRUE;
	size_t len = strlen(cfgdir);

	xstrlcpy(cfgdir + len, "/.lastd", 8);
	DPRINTF_S(cfgdir);

	FILE *fp = fopen(cfgdir, "w");

	if (fp) {
		if (fprintf(fp, "cd \"%s\"", curpath) < 0)
			ret = FALSE;

		fclose(fp);
	} else
		ret = FALSE;

	return ret;
}