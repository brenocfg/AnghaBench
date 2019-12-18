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
typedef  int /*<<< orphan*/  THREAD_EVENT_HANDLER ;
typedef  int /*<<< orphan*/  CRYPTO_THREAD_LOCAL ;

/* Variables and functions */
 int /*<<< orphan*/ ** CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  init_thread_push_handlers (int /*<<< orphan*/ **) ; 

__attribute__((used)) static THREAD_EVENT_HANDLER **
init_get_thread_local(CRYPTO_THREAD_LOCAL *local, int alloc, int keep)
{
    THREAD_EVENT_HANDLER **hands = CRYPTO_THREAD_get_local(local);

    if (alloc) {
        if (hands == NULL) {

            if ((hands = OPENSSL_zalloc(sizeof(*hands))) == NULL)
                return NULL;

            if (!CRYPTO_THREAD_set_local(local, hands)) {
                OPENSSL_free(hands);
                return NULL;
            }

#ifndef FIPS_MODE
            if (!init_thread_push_handlers(hands)) {
                CRYPTO_THREAD_set_local(local, NULL);
                OPENSSL_free(hands);
                return NULL;
            }
#endif
        }
    } else if (!keep) {
        CRYPTO_THREAD_set_local(local, NULL);
    }

    return hands;
}