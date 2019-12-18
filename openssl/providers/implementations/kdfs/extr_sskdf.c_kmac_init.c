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
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;

/* Variables and functions */
 scalar_t__ EVP_MAC_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t EVP_MAX_MD_SIZE ; 
 unsigned char* OPENSSL_zalloc (size_t) ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_CUSTOM ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_SIZE ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_size_t (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int kmac_init(EVP_MAC_CTX *ctx, const unsigned char *custom,
                     size_t custom_len, size_t kmac_out_len,
                     size_t derived_key_len, unsigned char **out)
{
    OSSL_PARAM params[2];

    /* Only KMAC has custom data - so return if not KMAC */
    if (custom == NULL)
        return 1;

    params[0] = OSSL_PARAM_construct_octet_string(OSSL_MAC_PARAM_CUSTOM,
                                                  (void *)custom, custom_len);
    params[1] = OSSL_PARAM_construct_end();

    if (!EVP_MAC_CTX_set_params(ctx, params))
        return 0;

    /* By default only do one iteration if kmac_out_len is not specified */
    if (kmac_out_len == 0)
        kmac_out_len = derived_key_len;
    /* otherwise check the size is valid */
    else if (!(kmac_out_len == derived_key_len
            || kmac_out_len == 20
            || kmac_out_len == 28
            || kmac_out_len == 32
            || kmac_out_len == 48
            || kmac_out_len == 64))
        return 0;

    params[0] = OSSL_PARAM_construct_size_t(OSSL_MAC_PARAM_SIZE,
                                            &kmac_out_len);

    if (EVP_MAC_CTX_set_params(ctx, params) <= 0)
        return 0;

    /*
     * For kmac the output buffer can be larger than EVP_MAX_MD_SIZE: so
     * alloc a buffer for this case.
     */
    if (kmac_out_len > EVP_MAX_MD_SIZE) {
        *out = OPENSSL_zalloc(kmac_out_len);
        if (*out == NULL)
            return 0;
    }
    return 1;
}