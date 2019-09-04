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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOSPC ; 
 char* kstrndup (char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __kstrncpy(char **dst, const char *name, size_t count, gfp_t gfp)
{
	*dst = kstrndup(name, count, gfp);
	if (!*dst)
		return -ENOSPC;
	return count;
}