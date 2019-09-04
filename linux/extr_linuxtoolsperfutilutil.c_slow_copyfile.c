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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsinfo__mountns_enter (struct nsinfo*,struct nscookie*) ; 
 int /*<<< orphan*/  nsinfo__mountns_exit (struct nscookie*) ; 

__attribute__((used)) static int slow_copyfile(const char *from, const char *to, struct nsinfo *nsi)
{
	int err = -1;
	char *line = NULL;
	size_t n;
	FILE *from_fp, *to_fp;
	struct nscookie nsc;

	nsinfo__mountns_enter(nsi, &nsc);
	from_fp = fopen(from, "r");
	nsinfo__mountns_exit(&nsc);
	if (from_fp == NULL)
		goto out;

	to_fp = fopen(to, "w");
	if (to_fp == NULL)
		goto out_fclose_from;

	while (getline(&line, &n, from_fp) > 0)
		if (fputs(line, to_fp) == EOF)
			goto out_fclose_to;
	err = 0;
out_fclose_to:
	fclose(to_fp);
	free(line);
out_fclose_from:
	fclose(from_fp);
out:
	return err;
}