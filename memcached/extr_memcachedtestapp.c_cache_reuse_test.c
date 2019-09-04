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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;
typedef  int /*<<< orphan*/  cache_t ;

/* Variables and functions */
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 char* cache_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cache_create (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_free (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static enum test_return cache_reuse_test(void)
{
    int ii;
    cache_t *cache = cache_create("test", sizeof(uint32_t), sizeof(char*),
                                  NULL, NULL);
    char *ptr = cache_alloc(cache);
    cache_free(cache, ptr);
    for (ii = 0; ii < 100; ++ii) {
        char *p = cache_alloc(cache);
        assert(p == ptr);
        cache_free(cache, ptr);
    }
    cache_destroy(cache);
    return TEST_PASS;
}