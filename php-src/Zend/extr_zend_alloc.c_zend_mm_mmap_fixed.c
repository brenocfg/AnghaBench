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
 int MAP_ANON ; 
 int MAP_EXCL ; 
 void* MAP_FAILED ; 
 int MAP_FIXED ; 
 int MAP_PRIVATE ; 
 int MEM_COMMIT ; 
 int MEM_RESERVE ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 void* VirtualAlloc (void*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_MM_FD ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 void* mmap (void*,size_t,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (void*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

__attribute__((used)) static void *zend_mm_mmap_fixed(void *addr, size_t size)
{
#ifdef _WIN32
	return VirtualAlloc(addr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
	int flags = MAP_PRIVATE | MAP_ANON;
#if defined(MAP_EXCL)
	flags |= MAP_FIXED | MAP_EXCL;
#endif
	/* MAP_FIXED leads to discarding of the old mapping, so it can't be used. */
	void *ptr = mmap(addr, size, PROT_READ | PROT_WRITE, flags /*| MAP_POPULATE | MAP_HUGETLB*/, ZEND_MM_FD, 0);

	if (ptr == MAP_FAILED) {
#if ZEND_MM_ERROR && !defined(MAP_EXCL)
		fprintf(stderr, "\nmmap() failed: [%d] %s\n", errno, strerror(errno));
#endif
		return NULL;
	} else if (ptr != addr) {
		if (munmap(ptr, size) != 0) {
#if ZEND_MM_ERROR
			fprintf(stderr, "\nmunmap() failed: [%d] %s\n", errno, strerror(errno));
#endif
		}
		return NULL;
	}
	return ptr;
#endif
}