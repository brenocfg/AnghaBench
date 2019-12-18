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
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  tls1_prf_P_hash (int /*<<< orphan*/ *,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char*,size_t) ; 

__attribute__((used)) static int tls1_prf_alg(EVP_MAC_CTX *mdctx, EVP_MAC_CTX *sha1ctx,
                        const unsigned char *sec, size_t slen,
                        const unsigned char *seed, size_t seed_len,
                        unsigned char *out, size_t olen)
{
    if (sha1ctx != NULL) {
        /* TLS v1.0 and TLS v1.1 */
        size_t i;
        unsigned char *tmp;
        /* calc: L_S1 = L_S2 = ceil(L_S / 2) */
        size_t L_S1 = (slen + 1) / 2;
        size_t L_S2 = L_S1;

        if (!tls1_prf_P_hash(mdctx, sec, L_S1,
                             seed, seed_len, out, olen))
            return 0;

        if ((tmp = OPENSSL_malloc(olen)) == NULL) {
            ERR_raise(ERR_LIB_PROV, ERR_R_MALLOC_FAILURE);
            return 0;
        }

        if (!tls1_prf_P_hash(sha1ctx, sec + slen - L_S2, L_S2,
                             seed, seed_len, tmp, olen)) {
            OPENSSL_clear_free(tmp, olen);
            return 0;
        }
        for (i = 0; i < olen; i++)
            out[i] ^= tmp[i];
        OPENSSL_clear_free(tmp, olen);
        return 1;
    }

    /* TLS v1.2 */
    if (!tls1_prf_P_hash(mdctx, sec, slen, seed, seed_len, out, olen))
        return 0;

    return 1;
}