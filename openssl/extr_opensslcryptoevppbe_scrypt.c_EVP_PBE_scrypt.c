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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PBE_SCRYPT ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MAXMEM_BYTES ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_PASS ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SALT ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SCRYPT_N ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SCRYPT_P ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SCRYPT_R ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_KDF_SCRYPT ; 
 int EVP_KDF_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EVP_R_PARAMETER_TOO_LARGE ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SCRYPT_MAX_MEM ; 
 scalar_t__ UINT32_MAX ; 

int EVP_PBE_scrypt(const char *pass, size_t passlen,
                   const unsigned char *salt, size_t saltlen,
                   uint64_t N, uint64_t r, uint64_t p, uint64_t maxmem,
                   unsigned char *key, size_t keylen)
{
    const char *empty = "";
    int rv = 1;
    EVP_KDF_CTX *kctx;

    if (r > UINT32_MAX || p > UINT32_MAX) {
        EVPerr(EVP_F_EVP_PBE_SCRYPT, EVP_R_PARAMETER_TOO_LARGE);
        return 0;
    }

    /* Maintain existing behaviour. */
    if (pass == NULL) {
        pass = empty;
        passlen = 0;
    }
    if (salt == NULL) {
        salt = (const unsigned char *)empty;
        saltlen = 0;
    }
    if (maxmem == 0)
        maxmem = SCRYPT_MAX_MEM;

    kctx = EVP_KDF_CTX_new_id(EVP_KDF_SCRYPT);
    if (kctx == NULL)
        return 0;

    if (EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_PASS, pass, (size_t)passlen) != 1
            || EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SALT,
                            salt, (size_t)saltlen) != 1
            || EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SCRYPT_N, N) != 1
            || EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SCRYPT_R, (uint32_t)r) != 1
            || EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SCRYPT_P, (uint32_t)p) != 1
            || EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_MAXMEM_BYTES, maxmem) != 1
            || EVP_KDF_derive(kctx, key, keylen) != 1)
        rv = 0;

    EVP_KDF_CTX_free(kctx);
    return rv;
}