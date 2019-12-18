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
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_sysvol_or_netlogon(const char *path)
{
	const char *s;
	char sep = path[0];

	s = strchr(path + 1, sep) + 1;
	return !strncasecmp(s, "sysvol", strlen("sysvol")) ||
		!strncasecmp(s, "netlogon", strlen("netlogon"));
}