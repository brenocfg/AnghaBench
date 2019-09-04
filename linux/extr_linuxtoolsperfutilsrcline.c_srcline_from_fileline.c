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
 scalar_t__ asprintf (char**,char*,char const*,unsigned int) ; 
 char* gnu_basename (char const*) ; 
 int /*<<< orphan*/  srcline_full_filename ; 

__attribute__((used)) static char *srcline_from_fileline(const char *file, unsigned int line)
{
	char *srcline;

	if (!file)
		return NULL;

	if (!srcline_full_filename)
		file = gnu_basename(file);

	if (asprintf(&srcline, "%s:%u", file, line) < 0)
		return NULL;

	return srcline;
}