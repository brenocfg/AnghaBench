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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_F_PKEY_DSA_CTRL_STR ; 
 int /*<<< orphan*/  DSA_R_INVALID_DIGEST_TYPE ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_CTX_set_dsa_paramgen_bits (int /*<<< orphan*/ *,int) ; 
 int EVP_PKEY_CTX_set_dsa_paramgen_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int EVP_PKEY_CTX_set_dsa_paramgen_q_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * EVP_get_digestbyname (char const*) ; 
 int atoi (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pkey_dsa_ctrl_str(EVP_PKEY_CTX *ctx,
                             const char *type, const char *value)
{
    if (strcmp(type, "dsa_paramgen_bits") == 0) {
        int nbits;
        nbits = atoi(value);
        return EVP_PKEY_CTX_set_dsa_paramgen_bits(ctx, nbits);
    }
    if (strcmp(type, "dsa_paramgen_q_bits") == 0) {
        int qbits = atoi(value);
        return EVP_PKEY_CTX_set_dsa_paramgen_q_bits(ctx, qbits);
    }
    if (strcmp(type, "dsa_paramgen_md") == 0) {
        const EVP_MD *md = EVP_get_digestbyname(value);

        if (md == NULL) {
            DSAerr(DSA_F_PKEY_DSA_CTRL_STR, DSA_R_INVALID_DIGEST_TYPE);
            return 0;
        }
        return EVP_PKEY_CTX_set_dsa_paramgen_md(ctx, md);
    }
    return -2;
}