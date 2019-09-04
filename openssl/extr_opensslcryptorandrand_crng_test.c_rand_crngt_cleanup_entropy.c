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
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_secure_clear_free (unsigned char*,size_t) ; 

void rand_crngt_cleanup_entropy(RAND_DRBG *drbg,
                                unsigned char *out, size_t outlen)
{
    OPENSSL_secure_clear_free(out, outlen);
}