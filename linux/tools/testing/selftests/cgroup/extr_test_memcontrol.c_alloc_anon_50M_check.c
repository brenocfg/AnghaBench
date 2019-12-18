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
 size_t MB (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 long cg_read_key_long (char const*,char*,char*) ; 
 long cg_read_long (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  values_close (long,long,int) ; 

__attribute__((used)) static int alloc_anon_50M_check(const char *cgroup, void *arg)
{
	size_t size = MB(50);
	char *buf, *ptr;
	long anon, current;
	int ret = -1;

	buf = malloc(size);
	for (ptr = buf; ptr < buf + size; ptr += PAGE_SIZE)
		*ptr = 0;

	current = cg_read_long(cgroup, "memory.current");
	if (current < size)
		goto cleanup;

	if (!values_close(size, current, 3))
		goto cleanup;

	anon = cg_read_key_long(cgroup, "memory.stat", "anon ");
	if (anon < 0)
		goto cleanup;

	if (!values_close(anon, current, 3))
		goto cleanup;

	ret = 0;
cleanup:
	free(buf);
	return ret;
}