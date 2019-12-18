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
typedef  int /*<<< orphan*/  EVP_ENCODE_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DecodeFinal (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_DecodeInit (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DecodeUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  EVP_ENCODE_CTX_USE_SRP_ALPHABET ; 
 int /*<<< orphan*/  EVP_ENCODE_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_ENCODE_CTX_new () ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  evp_encode_ctx_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int t_fromb64(unsigned char *a, size_t alen, const char *src)
{
    EVP_ENCODE_CTX *ctx;
    int outl = 0, outl2 = 0;
    size_t size, padsize;
    const unsigned char *pad = (const unsigned char *)"00";

    while (*src == ' ' || *src == '\t' || *src == '\n')
        ++src;
    size = strlen(src);
    padsize = 4 - (size & 3);
    padsize &= 3;

    /* Four bytes in src become three bytes output. */
    if (size > INT_MAX || ((size + padsize) / 4) * 3 > alen)
        return -1;

    ctx = EVP_ENCODE_CTX_new();
    if (ctx == NULL)
        return -1;

    /*
     * This should never occur because 1 byte of data always requires 2 bytes of
     * encoding, i.e.
     *  0 bytes unencoded = 0 bytes encoded
     *  1 byte unencoded  = 2 bytes encoded
     *  2 bytes unencoded = 3 bytes encoded
     *  3 bytes unencoded = 4 bytes encoded
     *  4 bytes unencoded = 6 bytes encoded
     *  etc
     */
    if (padsize == 3) {
        outl = -1;
        goto err;
    }

    /* Valid padsize values are now 0, 1 or 2 */

    EVP_DecodeInit(ctx);
    evp_encode_ctx_set_flags(ctx, EVP_ENCODE_CTX_USE_SRP_ALPHABET);

    /* Add any encoded padding that is required */
    if (padsize != 0
            && EVP_DecodeUpdate(ctx, a, &outl, pad, padsize) < 0) {
        outl = -1;
        goto err;
    }
    if (EVP_DecodeUpdate(ctx, a, &outl2, (const unsigned char *)src, size) < 0) {
        outl = -1;
        goto err;
    }
    outl += outl2;
    EVP_DecodeFinal(ctx, a + outl, &outl2);
    outl += outl2;

    /* Strip off the leading padding */
    if (padsize != 0) {
        if ((int)padsize >= outl) {
            outl = -1;
            goto err;
        }

        /*
         * If we added 1 byte of padding prior to encoding then we have 2 bytes
         * of "real" data which gets spread across 4 encoded bytes like this:
         *   (6 bits pad)(2 bits pad | 4 bits data)(6 bits data)(6 bits data)
         * So 1 byte of pre-encoding padding results in 1 full byte of encoded
         * padding.
         * If we added 2 bytes of padding prior to encoding this gets encoded
         * as:
         *   (6 bits pad)(6 bits pad)(4 bits pad | 2 bits data)(6 bits data)
         * So 2 bytes of pre-encoding padding results in 2 full bytes of encoded
         * padding, i.e. we have to strip the same number of bytes of padding
         * from the encoded data as we added to the pre-encoded data.
         */
        memmove(a, a + padsize, outl - padsize);
        outl -= padsize;
    }

 err:
    EVP_ENCODE_CTX_free(ctx);

    return outl;
}