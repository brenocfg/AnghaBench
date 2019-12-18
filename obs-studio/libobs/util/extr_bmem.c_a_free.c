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
 int /*<<< orphan*/  _aligned_free (void*) ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static void a_free(void *ptr)
{
#ifdef ALIGNED_MALLOC
	_aligned_free(ptr);
#elif ALIGNMENT_HACK
	if (ptr)
		free((char *)ptr - ((char *)ptr)[-1]);
#else
	free(ptr);
#endif
}