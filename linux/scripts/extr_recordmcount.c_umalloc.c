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
 int /*<<< orphan*/  file_append_cleanup () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  mmap_cleanup () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void * umalloc(size_t size)
{
	void *const addr = malloc(size);
	if (addr == 0) {
		fprintf(stderr, "malloc failed: %zu bytes\n", size);
		file_append_cleanup();
		mmap_cleanup();
		return NULL;
	}
	return addr;
}