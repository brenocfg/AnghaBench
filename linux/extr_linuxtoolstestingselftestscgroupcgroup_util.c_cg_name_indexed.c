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
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*,int) ; 
 int strlen (char const*) ; 

char *cg_name_indexed(const char *root, const char *name, int index)
{
	size_t len = strlen(root) + strlen(name) + 10;
	char *ret = malloc(len);

	snprintf(ret, len, "%s/%s_%d", root, name, index);

	return ret;
}