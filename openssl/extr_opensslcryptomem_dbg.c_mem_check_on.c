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
typedef  int /*<<< orphan*/  CRYPTO_THREAD_ID ;

/* Variables and functions */
 int CRYPTO_MEM_CHECK_ENABLE ; 
 int CRYPTO_MEM_CHECK_ON ; 
 int /*<<< orphan*/  CRYPTO_THREAD_compare_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_get_current_id () ; 
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disabling_threadid ; 
 int /*<<< orphan*/  do_memdbg_init ; 
 int /*<<< orphan*/  memdbg_init ; 
 int /*<<< orphan*/  memdbg_lock ; 
 int mh_mode ; 

__attribute__((used)) static int mem_check_on(void)
{
    int ret = 0;
    CRYPTO_THREAD_ID cur;

    if (mh_mode & CRYPTO_MEM_CHECK_ON) {
        if (!RUN_ONCE(&memdbg_init, do_memdbg_init))
            return 0;

        cur = CRYPTO_THREAD_get_current_id();
        CRYPTO_THREAD_read_lock(memdbg_lock);

        ret = (mh_mode & CRYPTO_MEM_CHECK_ENABLE)
            || !CRYPTO_THREAD_compare_id(disabling_threadid, cur);

        CRYPTO_THREAD_unlock(memdbg_lock);
    }
    return ret;
}