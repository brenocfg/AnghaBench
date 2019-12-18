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
struct dso {char* symsrc_filename; char* long_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static const char *dso__name(struct dso *dso)
{
	const char *dso_name;

	if (dso->symsrc_filename)
		dso_name = dso->symsrc_filename;
	else
		dso_name = dso->long_name;

	if (dso_name[0] == '[')
		return NULL;

	if (!strncmp(dso_name, "/tmp/perf-", 10))
		return NULL;

	return dso_name;
}