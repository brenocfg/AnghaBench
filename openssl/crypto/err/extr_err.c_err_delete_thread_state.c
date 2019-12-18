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
typedef  int /*<<< orphan*/  ERR_STATE ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_STATE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err_thread_local ; 

__attribute__((used)) static void err_delete_thread_state(void *arg)
{
    ERR_STATE *state = CRYPTO_THREAD_get_local(&err_thread_local);
    if (state == NULL)
        return;

    CRYPTO_THREAD_set_local(&err_thread_local, NULL);
    ERR_STATE_free(state);
}