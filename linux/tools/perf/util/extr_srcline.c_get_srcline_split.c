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
typedef  int /*<<< orphan*/  u64 ;
struct dso {scalar_t__ a2l_fails; scalar_t__ has_srcline; } ;

/* Variables and functions */
 scalar_t__ A2L_FAIL_LIMIT ; 
 int /*<<< orphan*/  addr2line (char const*,int /*<<< orphan*/ ,char**,unsigned int*,struct dso*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dso__free_a2l (struct dso*) ; 
 char* dso__name (struct dso*) ; 

char *get_srcline_split(struct dso *dso, u64 addr, unsigned *line)
{
	char *file = NULL;
	const char *dso_name;

	if (!dso->has_srcline)
		goto out;

	dso_name = dso__name(dso);
	if (dso_name == NULL)
		goto out;

	if (!addr2line(dso_name, addr, &file, line, dso, true, NULL, NULL))
		goto out;

	dso->a2l_fails = 0;
	return file;

out:
	if (dso->a2l_fails && ++dso->a2l_fails > A2L_FAIL_LIMIT) {
		dso->has_srcline = 0;
		dso__free_a2l(dso);
	}

	return NULL;
}