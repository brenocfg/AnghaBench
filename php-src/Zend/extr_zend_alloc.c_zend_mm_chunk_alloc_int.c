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
 int /*<<< orphan*/  MADV_HUGEPAGE ; 
 size_t REAL_PAGE_SIZE ; 
 size_t ZEND_MM_ALIGNED_OFFSET (void*,size_t) ; 
 int /*<<< orphan*/  madvise (void*,size_t,int /*<<< orphan*/ ) ; 
 void* zend_mm_mmap (size_t) ; 
 void* zend_mm_mmap_fixed (void*,size_t) ; 
 int /*<<< orphan*/  zend_mm_munmap (char*,size_t) ; 
 scalar_t__ zend_mm_use_huge_pages ; 

__attribute__((used)) static void *zend_mm_chunk_alloc_int(size_t size, size_t alignment)
{
	void *ptr = zend_mm_mmap(size);

	if (ptr == NULL) {
		return NULL;
	} else if (ZEND_MM_ALIGNED_OFFSET(ptr, alignment) == 0) {
#ifdef MADV_HUGEPAGE
		if (zend_mm_use_huge_pages) {
			madvise(ptr, size, MADV_HUGEPAGE);
		}
#endif
		return ptr;
	} else {
		size_t offset;

		/* chunk has to be aligned */
		zend_mm_munmap(ptr, size);
		ptr = zend_mm_mmap(size + alignment - REAL_PAGE_SIZE);
#ifdef _WIN32
		offset = ZEND_MM_ALIGNED_OFFSET(ptr, alignment);
		zend_mm_munmap(ptr, size + alignment - REAL_PAGE_SIZE);
		ptr = zend_mm_mmap_fixed((void*)((char*)ptr + (alignment - offset)), size);
		offset = ZEND_MM_ALIGNED_OFFSET(ptr, alignment);
		if (offset != 0) {
			zend_mm_munmap(ptr, size);
			return NULL;
		}
		return ptr;
#else
		offset = ZEND_MM_ALIGNED_OFFSET(ptr, alignment);
		if (offset != 0) {
			offset = alignment - offset;
			zend_mm_munmap(ptr, offset);
			ptr = (char*)ptr + offset;
			alignment -= offset;
		}
		if (alignment > REAL_PAGE_SIZE) {
			zend_mm_munmap((char*)ptr + size, alignment - REAL_PAGE_SIZE);
		}
# ifdef MADV_HUGEPAGE
		if (zend_mm_use_huge_pages) {
			madvise(ptr, size, MADV_HUGEPAGE);
		}
# endif
#endif
		return ptr;
	}
}