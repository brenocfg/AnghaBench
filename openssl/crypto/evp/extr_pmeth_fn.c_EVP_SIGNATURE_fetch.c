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
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EVP_SIGNATURE ;

/* Variables and functions */
 scalar_t__ EVP_SIGNATURE_free ; 
 scalar_t__ EVP_SIGNATURE_up_ref ; 
 int /*<<< orphan*/  OSSL_OP_SIGNATURE ; 
 int /*<<< orphan*/ * evp_generic_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int (*) (void*),void (*) (void*)) ; 
 int /*<<< orphan*/  evp_signature_from_dispatch ; 

EVP_SIGNATURE *EVP_SIGNATURE_fetch(OPENSSL_CTX *ctx, const char *algorithm,
                                   const char *properties)
{
    return evp_generic_fetch(ctx, OSSL_OP_SIGNATURE, algorithm, properties,
                             evp_signature_from_dispatch,
                             (int (*)(void *))EVP_SIGNATURE_up_ref,
                             (void (*)(void *))EVP_SIGNATURE_free);
}