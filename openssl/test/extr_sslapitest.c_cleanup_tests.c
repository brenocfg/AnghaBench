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
 int /*<<< orphan*/  bio_s_always_retry_free () ; 
 int /*<<< orphan*/  bio_s_mempacket_test_free () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  privkey ; 

void cleanup_tests(void)
{
    OPENSSL_free(cert);
    OPENSSL_free(privkey);
    bio_s_mempacket_test_free();
    bio_s_always_retry_free();
}