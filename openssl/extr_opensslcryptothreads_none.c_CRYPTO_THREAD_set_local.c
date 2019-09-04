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
 size_t OPENSSL_CRYPTO_THREAD_LOCAL_KEY_MAX ; 
 void** thread_local_storage ; 

int CRYPTO_THREAD_set_local(CRYPTO_THREAD_LOCAL *key, void *val)
{
    if (*key >= OPENSSL_CRYPTO_THREAD_LOCAL_KEY_MAX)
        return 0;

    thread_local_storage[*key] = val;

    return 1;
}