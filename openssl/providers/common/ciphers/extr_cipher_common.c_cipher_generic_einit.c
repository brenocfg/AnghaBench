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
typedef  int /*<<< orphan*/  PROV_CIPHER_CTX ;

/* Variables and functions */
 int cipher_generic_init_internal (int /*<<< orphan*/ *,unsigned char const*,size_t,unsigned char const*,size_t,int) ; 

int cipher_generic_einit(void *vctx, const unsigned char *key, size_t keylen,
                         const unsigned char *iv, size_t ivlen)
{
    return cipher_generic_init_internal((PROV_CIPHER_CTX *)vctx, key, keylen,
                                        iv, ivlen, 1);
}