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
 int /*<<< orphan*/  ALIGNMENT ; 
 void* _aligned_realloc (void*,size_t,int /*<<< orphan*/ ) ; 
 void* a_malloc (size_t) ; 
 void* realloc (void*,size_t) ; 

__attribute__((used)) static void *a_realloc(void *ptr, size_t size)
{
#ifdef ALIGNED_MALLOC
	return _aligned_realloc(ptr, size, ALIGNMENT);
#elif ALIGNMENT_HACK
	long diff;

	if (!ptr)
		return a_malloc(size);
	diff = ((char *)ptr)[-1];
	ptr = realloc((char *)ptr - diff, size + diff);
	if (ptr)
		ptr = (char *)ptr + diff;
	return ptr;
#else
	return realloc(ptr, size);
#endif
}