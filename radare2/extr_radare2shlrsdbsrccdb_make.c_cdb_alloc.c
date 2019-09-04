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
typedef  int /*<<< orphan*/  ut32 ;

/* Variables and functions */
 char* malloc (int /*<<< orphan*/ ) ; 

char *cdb_alloc(ut32 n) {
#if __APPLE__ && !__POWERPC__
	void *ret = NULL;
	return posix_memalign (&ret, ALIGNMENT, n)? NULL: ret;
#elif __SDB_WINDOWS__ && !__CYGWIN__
	return _aligned_malloc (n, ALIGNMENT);
#else
	return malloc (n);
#endif
}