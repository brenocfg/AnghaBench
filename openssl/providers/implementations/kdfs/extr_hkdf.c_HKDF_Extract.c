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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * HMAC (int /*<<< orphan*/  const*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROV_R_WRONG_OUTPUT_BUFFER_SIZE ; 

__attribute__((used)) static int HKDF_Extract(const EVP_MD *evp_md,
                        const unsigned char *salt, size_t salt_len,
                        const unsigned char *ikm, size_t ikm_len,
                        unsigned char *prk, size_t prk_len)
{
    int sz = EVP_MD_size(evp_md);

    if (sz < 0)
        return 0;
    if (prk_len != (size_t)sz) {
        ERR_raise(ERR_LIB_PROV, PROV_R_WRONG_OUTPUT_BUFFER_SIZE);
        return 0;
    }
    /* calc: PRK = HMAC-Hash(salt, IKM) */
    return HMAC(evp_md, salt, salt_len, ikm, ikm_len, prk, NULL) != NULL;
}