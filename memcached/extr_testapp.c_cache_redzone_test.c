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
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;
typedef  int /*<<< orphan*/  cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int TEST_PASS ; 
 int TEST_SKIP ; 
 int /*<<< orphan*/  assert (int) ; 
 char* cache_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cache_create (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_destroy (int /*<<< orphan*/ *) ; 
 int cache_error ; 
 int /*<<< orphan*/  cache_free (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum test_return cache_redzone_test(void)
{
#ifndef HAVE_UMEM_H
    cache_t *cache = cache_create("test", sizeof(uint32_t), sizeof(char*),
                                  NULL, NULL);

    /* Ignore SIGABRT */
    struct sigaction old_action;
    struct sigaction action = { .sa_handler = SIG_IGN, .sa_flags = 0};
    sigemptyset(&action.sa_mask);
    sigaction(SIGABRT, &action, &old_action);

    /* check memory debug.. */
    char *p = cache_alloc(cache);
    char old = *(p - 1);
    *(p - 1) = 0;
    cache_free(cache, p);
    assert(cache_error == -1);
    *(p - 1) = old;

    p[sizeof(uint32_t)] = 0;
    cache_free(cache, p);
    assert(cache_error == 1);

    /* restore signal handler */
    sigaction(SIGABRT, &old_action, NULL);

    cache_destroy(cache);

    return TEST_PASS;
#else
    return TEST_SKIP;
#endif
}