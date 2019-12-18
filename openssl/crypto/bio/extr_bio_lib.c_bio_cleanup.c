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
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bio_lookup_lock ; 
 int /*<<< orphan*/  bio_sock_cleanup_int () ; 
 int /*<<< orphan*/ * bio_type_lock ; 

void bio_cleanup(void)
{
#ifndef OPENSSL_NO_SOCK
    bio_sock_cleanup_int();
    CRYPTO_THREAD_lock_free(bio_lookup_lock);
    bio_lookup_lock = NULL;
#endif
    CRYPTO_THREAD_lock_free(bio_type_lock);
    bio_type_lock = NULL;
}