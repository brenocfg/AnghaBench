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
 int TEST_FAIL ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* cache_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cache_create (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_destructor ; 
 int /*<<< orphan*/  cache_free (int /*<<< orphan*/ *,char*) ; 
 char* destruct_data ; 

__attribute__((used)) static enum test_return cache_destructor_test(void)
{
    cache_t *cache = cache_create("test", sizeof(uint32_t), sizeof(char*),
                                  NULL, cache_destructor);
    assert(cache != NULL);
    char *ptr = cache_alloc(cache);
    cache_free(cache, ptr);
    cache_destroy(cache);

    return (ptr == destruct_data) ? TEST_PASS : TEST_FAIL;
}