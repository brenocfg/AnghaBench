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
 int scnprintf (char*,size_t,char*,char const*,char*,char const*) ; 

int path__join(char *bf, size_t size, const char *path1, const char *path2)
{
	return scnprintf(bf, size, "%s%s%s", path1, path1[0] ? "/" : "", path2);
}