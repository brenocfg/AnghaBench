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
 int /*<<< orphan*/  MEM_RELEASE ; 
 scalar_t__ VirtualFree (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ munmap (void*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stderr_last_error (char*) ; 
 char* strerror (int) ; 

__attribute__((used)) static void zend_mm_munmap(void *addr, size_t size)
{
#ifdef _WIN32
	if (VirtualFree(addr, 0, MEM_RELEASE) == 0) {
#if ZEND_MM_ERROR
		stderr_last_error("VirtualFree() failed");
#endif
	}
#else
	if (munmap(addr, size) != 0) {
#if ZEND_MM_ERROR
		fprintf(stderr, "\nmunmap() failed: [%d] %s\n", errno, strerror(errno));
#endif
	}
#endif
}