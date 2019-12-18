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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ lookup_path (char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const* const,char const*) ; 

__attribute__((used)) static int lookup_triplets(const char *const *triplets, const char *name)
{
	int i;
	char buf[PATH_MAX];

	for (i = 0; triplets[i] != NULL; i++) {
		scnprintf(buf, sizeof(buf), "%s%s", triplets[i], name);
		if (lookup_path(buf))
			return i;
	}
	return -1;
}