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
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_f_tls_corrupt_filter_free () ; 
 int /*<<< orphan*/  cipher_list ; 

void cleanup_tests(void)
{
    bio_f_tls_corrupt_filter_free();
    OPENSSL_free(cipher_list);
}