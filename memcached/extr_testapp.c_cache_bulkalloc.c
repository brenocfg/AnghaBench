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
typedef  enum test_return { ____Placeholder_test_return } test_return ;
typedef  int /*<<< orphan*/  cache_t ;

/* Variables and functions */
 int ITERATIONS ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 void* cache_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cache_create (char*,size_t,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_free (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 

__attribute__((used)) static enum test_return cache_bulkalloc(size_t datasize)
{
    cache_t *cache = cache_create("test", datasize, sizeof(char*),
                                  NULL, NULL);
#define ITERATIONS 1024
    void *ptr[ITERATIONS];

    for (int ii = 0; ii < ITERATIONS; ++ii) {
        ptr[ii] = cache_alloc(cache);
        assert(ptr[ii] != 0);
        memset(ptr[ii], 0xff, datasize);
    }

    for (int ii = 0; ii < ITERATIONS; ++ii) {
        cache_free(cache, ptr[ii]);
    }

#undef ITERATIONS
    cache_destroy(cache);
    return TEST_PASS;
}