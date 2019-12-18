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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int CRYPTO_mem_leaks_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_free_ex_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_bio ; 

int CRYPTO_mem_leaks(BIO *b)
{
    /*
     * OPENSSL_cleanup() will free the ex_data locks so we can't have any
     * ex_data hanging around
     */
    bio_free_ex_data(b);

    return CRYPTO_mem_leaks_cb(print_bio, b);
}