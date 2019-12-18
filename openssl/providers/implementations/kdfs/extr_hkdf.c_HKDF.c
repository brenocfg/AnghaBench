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
typedef  int /*<<< orphan*/  prk ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int HKDF_Expand (int /*<<< orphan*/  const*,unsigned char*,size_t,unsigned char const*,size_t,unsigned char*,size_t) ; 
 int /*<<< orphan*/  HKDF_Extract (int /*<<< orphan*/  const*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 

__attribute__((used)) static int HKDF(const EVP_MD *evp_md,
                const unsigned char *salt, size_t salt_len,
                const unsigned char *ikm, size_t ikm_len,
                const unsigned char *info, size_t info_len,
                unsigned char *okm, size_t okm_len)
{
    unsigned char prk[EVP_MAX_MD_SIZE];
    int ret, sz;
    size_t prk_len;

    sz = EVP_MD_size(evp_md);
    if (sz < 0)
        return 0;
    prk_len = (size_t)sz;

    /* Step 1: HKDF-Extract(salt, IKM) -> PRK */
    if (!HKDF_Extract(evp_md, salt, salt_len, ikm, ikm_len, prk, prk_len))
        return 0;

    /* Step 2: HKDF-Expand(PRK, info, L) -> OKM */
    ret = HKDF_Expand(evp_md, prk, prk_len, info, info_len, okm, okm_len);
    OPENSSL_cleanse(prk, sizeof(prk));

    return ret;
}