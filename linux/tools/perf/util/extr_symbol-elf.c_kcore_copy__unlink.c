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
 int PATH_MAX ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*,char const*) ; 
 int unlink (char*) ; 

__attribute__((used)) static int kcore_copy__unlink(const char *dir, const char *name)
{
	char filename[PATH_MAX];

	scnprintf(filename, PATH_MAX, "%s/%s", dir, name);

	return unlink(filename);
}