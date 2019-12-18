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
 int /*<<< orphan*/  ASYNC_is_capable () ; 
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_ON ; 
 int /*<<< orphan*/  CRYPTO_mem_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_set_mem_debug (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_ASYNC_WAIT_CTX_get_all_fds () ; 
 int /*<<< orphan*/  test_ASYNC_block_pause () ; 
 int /*<<< orphan*/  test_ASYNC_callback_status () ; 
 int /*<<< orphan*/  test_ASYNC_get_current_job () ; 
 int /*<<< orphan*/  test_ASYNC_init_thread () ; 
 int /*<<< orphan*/  test_ASYNC_start_job () ; 

int main(int argc, char **argv)
{
    if (!ASYNC_is_capable()) {
        fprintf(stderr,
                "OpenSSL build is not ASYNC capable - skipping async tests\n");
    } else {
        CRYPTO_set_mem_debug(1);
        CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

        if (       !test_ASYNC_init_thread()
                || !test_ASYNC_callback_status()
                || !test_ASYNC_start_job()
                || !test_ASYNC_get_current_job()
                || !test_ASYNC_WAIT_CTX_get_all_fds()
                || !test_ASYNC_block_pause()) {
            return 1;
        }
    }
    printf("PASS\n");
    return 0;
}