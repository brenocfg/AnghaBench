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
 int EVP_ENCODE_CTX_NO_NEWLINES ; 
 int EVP_ENCODE_CTX_USE_SRP_ALPHABET ; 
 int /*<<< orphan*/  EVP_ENCODE_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_ENCODE_CTX_new () ; 
 int /*<<< orphan*/  EVP_EncodeFinal (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_EncodeInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_EncodeUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char const*,int) ; 
 int /*<<< orphan*/  evp_encode_ctx_set_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static int t_tob64(char *dst, const unsigned char *src, int size)
{
    EVP_ENCODE_CTX *ctx = EVP_ENCODE_CTX_new();
    int outl = 0, outl2 = 0;
    unsigned char pad[2] = {0, 0};
    size_t leadz = 0;

    if (ctx == NULL)
        return 0;

    EVP_EncodeInit(ctx);
    evp_encode_ctx_set_flags(ctx, EVP_ENCODE_CTX_NO_NEWLINES
                                  | EVP_ENCODE_CTX_USE_SRP_ALPHABET);

    /*
     * We pad at the front with zero bytes until the length is a multiple of 3
     * so that EVP_EncodeUpdate/EVP_EncodeFinal does not add any of its own "="
     * padding
     */
    leadz = 3 - (size % 3);
    if (leadz != 3
            && !EVP_EncodeUpdate(ctx, (unsigned char *)dst, &outl, pad,
                                 leadz)) {
        EVP_ENCODE_CTX_free(ctx);
        return 0;
    }

    if (!EVP_EncodeUpdate(ctx, (unsigned char *)dst + outl, &outl2, src,
                          size)) {
        EVP_ENCODE_CTX_free(ctx);
        return 0;
    }
    outl += outl2;
    EVP_EncodeFinal(ctx, (unsigned char *)dst + outl, &outl2);
    outl += outl2;

    /* Strip the encoded padding at the front */
    if (leadz != 3) {
        memmove(dst, dst + leadz, outl - leadz);
        dst[outl - leadz] = '\0';
    }

    EVP_ENCODE_CTX_free(ctx);
    return 1;
}