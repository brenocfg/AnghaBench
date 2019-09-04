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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 int called_encrypt ; 

__attribute__((used)) static int test_encrypt(EVP_PKEY_CTX *ctx, unsigned char *sig,
                        size_t *siglen, const unsigned char *tbs, size_t tbslen)
{
    called_encrypt = 1;
    return 1;
}