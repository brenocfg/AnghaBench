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
 int PAGE_SIZE ; 
 long atol (char*) ; 
 scalar_t__ cg_read (char const*,char const*,char*,int) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char const*) ; 

long cg_read_key_long(const char *cgroup, const char *control, const char *key)
{
	char buf[PAGE_SIZE];
	char *ptr;

	if (cg_read(cgroup, control, buf, sizeof(buf)))
		return -1;

	ptr = strstr(buf, key);
	if (!ptr)
		return -1;

	return atol(ptr + strlen(key));
}