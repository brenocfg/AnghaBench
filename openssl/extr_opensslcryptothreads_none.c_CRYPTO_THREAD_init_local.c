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
typedef  size_t CRYPTO_THREAD_LOCAL ;

/* Variables and functions */
 unsigned int OPENSSL_CRYPTO_THREAD_LOCAL_KEY_MAX ; 
 int /*<<< orphan*/ ** thread_local_storage ; 

int CRYPTO_THREAD_init_local(CRYPTO_THREAD_LOCAL *key, void (*cleanup)(void *))
{
    static unsigned int thread_local_key = 0;

    if (thread_local_key >= OPENSSL_CRYPTO_THREAD_LOCAL_KEY_MAX)
        return 0;

    *key = thread_local_key++;

    thread_local_storage[*key] = NULL;

    return 1;
}