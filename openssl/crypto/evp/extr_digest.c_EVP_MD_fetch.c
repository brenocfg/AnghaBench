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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_OP_DIGEST ; 
 int /*<<< orphan*/ * evp_generic_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evp_md_free ; 
 int /*<<< orphan*/  evp_md_from_dispatch ; 
 int /*<<< orphan*/  evp_md_up_ref ; 

EVP_MD *EVP_MD_fetch(OPENSSL_CTX *ctx, const char *algorithm,
                     const char *properties)
{
    EVP_MD *md =
        evp_generic_fetch(ctx, OSSL_OP_DIGEST, algorithm, properties,
                          evp_md_from_dispatch, evp_md_up_ref, evp_md_free);

    return md;
}