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
 void* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *zend_mm_mmap(size_t size)
{
#ifdef _WIN32
	void *ptr = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (ptr == NULL) {
#if ZEND_MM_ERROR
		stderr_last_error("VirtualAlloc() failed");
#endif
		return NULL;
	}
	return ptr;
#else
	void *ptr;

#ifdef MAP_HUGETLB
	if (zend_mm_use_huge_pages && size == ZEND_MM_CHUNK_SIZE) {
		ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_HUGETLB, -1, 0);
		if (ptr != MAP_FAILED) {
			return ptr;
		}
	}
#endif

	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

	if (ptr == MAP_FAILED) {
#if ZEND_MM_ERROR
		fprintf(stderr, "\nmmap() failed: [%d] %s\n", errno, strerror(errno));
#endif
		return NULL;
	}
	return ptr;
#endif
}