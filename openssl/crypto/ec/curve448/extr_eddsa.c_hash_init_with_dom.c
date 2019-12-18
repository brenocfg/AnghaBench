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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  dom ;
typedef  int /*<<< orphan*/  c448_error_t ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  C448_FAILURE ; 
 int /*<<< orphan*/  C448_SUCCESS ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/ * EVP_MD_fetch (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_free (int /*<<< orphan*/ *) ; 
 size_t UINT8_MAX ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static c448_error_t hash_init_with_dom(OPENSSL_CTX *ctx, EVP_MD_CTX *hashctx,
                                       uint8_t prehashed,
                                       uint8_t for_prehash,
                                       const uint8_t *context,
                                       size_t context_len)
{
    const char *dom_s = "SigEd448";
    uint8_t dom[2];
    EVP_MD *shake256 = NULL;

    if (context_len > UINT8_MAX)
        return C448_FAILURE;

    dom[0] = (uint8_t)(2 - (prehashed == 0 ? 1 : 0)
                       - (for_prehash == 0 ? 1 : 0));
    dom[1] = (uint8_t)context_len;

    shake256 = EVP_MD_fetch(ctx, "SHAKE256", NULL);
    if (shake256 == NULL)
        return C448_FAILURE;

    if (!EVP_DigestInit_ex(hashctx, shake256, NULL)
            || !EVP_DigestUpdate(hashctx, dom_s, strlen(dom_s))
            || !EVP_DigestUpdate(hashctx, dom, sizeof(dom))
            || !EVP_DigestUpdate(hashctx, context, context_len)) {
        EVP_MD_free(shake256);
        return C448_FAILURE;
    }

    EVP_MD_free(shake256);
    return C448_SUCCESS;
}