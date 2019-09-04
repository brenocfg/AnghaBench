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
 int EIO ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int split_string(char *buf, char **a, char **b, char **c, char **d)
{
	*a = strsep(&buf, ":");
	if (!*a)
		return -EIO;

	*b = strsep(&buf, ":\n");
	if (!*b)
		return -EIO;

	*c = strsep(&buf, ":\n");
	if (!*c)
		return -EIO;

	if (d)
		*d = strsep(&buf, ":\n");

	return 0;
}