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
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static const char *guess_type_by_name(const char *fname, const char *fallback)
{
	const char *s;

	s = strrchr(fname, '.');
	if (s == NULL)
		return fallback;
	if (!strcasecmp(s, ".dts"))
		return "dts";
	if (!strcasecmp(s, ".yaml"))
		return "yaml";
	if (!strcasecmp(s, ".dtb"))
		return "dtb";
	return fallback;
}