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
 scalar_t__ PATH_MAX ; 
 scalar_t__ istopdir (char const*) ; 
 size_t xstrlcpy (char*,char const*,scalar_t__) ; 

__attribute__((used)) static size_t mkpath(const char *dir, const char *name, char *out)
{
	size_t len;

	/* Handle absolute path */
	if (name[0] == '/')
		return xstrlcpy(out, name, PATH_MAX);

	/* Handle root case */
	if (istopdir(dir))
		len = 1;
	else
		len = xstrlcpy(out, dir, PATH_MAX);

	out[len - 1] = '/'; // NOLINT
	return (xstrlcpy(out + len, name, PATH_MAX - len) + len);
}