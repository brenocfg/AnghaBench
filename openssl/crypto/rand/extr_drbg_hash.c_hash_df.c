#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned char* vtmp; size_t blocklen; int /*<<< orphan*/  md; int /*<<< orphan*/ * ctx; } ;
struct TYPE_5__ {TYPE_2__ hash; } ;
struct TYPE_7__ {size_t seedlen; TYPE_1__ data; } ;
typedef  TYPE_2__ RAND_DRBG_HASH ;
typedef  TYPE_3__ RAND_DRBG ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 unsigned char const INBYTE_IGNORE ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int hash_df(RAND_DRBG *drbg, unsigned char *out,
                   const unsigned char inbyte,
                   const unsigned char *in, size_t inlen,
                   const unsigned char *in2, size_t in2len,
                   const unsigned char *in3, size_t in3len)
{
    RAND_DRBG_HASH *hash = &drbg->data.hash;
    EVP_MD_CTX *ctx = hash->ctx;
    unsigned char *vtmp = hash->vtmp;
    /* tmp = counter || num_bits_returned || [inbyte] */
    unsigned char tmp[1 + 4 + 1];
    int tmp_sz = 0;
    size_t outlen = drbg->seedlen;
    size_t num_bits_returned = outlen * 8;
    /*
     * No need to check outlen size here, as the standard only ever needs
     * seedlen bytes which is always less than the maximum permitted.
     */

    /* (Step 3) counter = 1 (tmp[0] is the 8 bit counter) */
    tmp[tmp_sz++] = 1;
    /* tmp[1..4] is the fixed 32 bit no_of_bits_to_return */
    tmp[tmp_sz++] = (unsigned char)((num_bits_returned >> 24) & 0xff);
    tmp[tmp_sz++] = (unsigned char)((num_bits_returned >> 16) & 0xff);
    tmp[tmp_sz++] = (unsigned char)((num_bits_returned >> 8) & 0xff);
    tmp[tmp_sz++] = (unsigned char)(num_bits_returned & 0xff);
    /* Tack the additional input byte onto the end of tmp if it exists */
    if (inbyte != INBYTE_IGNORE)
        tmp[tmp_sz++] = inbyte;

    /* (Step 4) */
    for (;;) {
        /*
         * (Step 4.1) out = out || Hash(tmp || in || [in2] || [in3])
         *            (where tmp = counter || num_bits_returned || [inbyte])
         */
        if (!(EVP_DigestInit_ex(ctx, hash->md, NULL)
                && EVP_DigestUpdate(ctx, tmp, tmp_sz)
                && EVP_DigestUpdate(ctx, in, inlen)
                && (in2 == NULL || EVP_DigestUpdate(ctx, in2, in2len))
                && (in3 == NULL || EVP_DigestUpdate(ctx, in3, in3len))))
            return 0;

        if (outlen < hash->blocklen) {
            if (!EVP_DigestFinal(ctx, vtmp, NULL))
                return 0;
            memcpy(out, vtmp, outlen);
            OPENSSL_cleanse(vtmp, hash->blocklen);
            break;
        } else if(!EVP_DigestFinal(ctx, out, NULL)) {
            return 0;
        }

        outlen -= hash->blocklen;
        if (outlen == 0)
            break;
        /* (Step 4.2) counter++ */
        tmp[0]++;
        out += hash->blocklen;
    }
    return 1;
}