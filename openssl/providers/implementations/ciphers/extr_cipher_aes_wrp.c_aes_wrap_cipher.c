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
typedef  int /*<<< orphan*/  PROV_AES_WRAP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_OUTPUT_BUFFER_TOO_SMALL ; 
 size_t aes_wrap_cipher_internal (int /*<<< orphan*/ *,unsigned char*,unsigned char const*,size_t) ; 

__attribute__((used)) static int aes_wrap_cipher(void *vctx,
                           unsigned char *out, size_t *outl, size_t outsize,
                           const unsigned char *in, size_t inl)
{
    PROV_AES_WRAP_CTX *ctx = (PROV_AES_WRAP_CTX *)vctx;
    size_t len;

    if (outsize < inl) {
        ERR_raise(ERR_LIB_PROV, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
        return -1;
    }

    len = aes_wrap_cipher_internal(ctx, out, in, inl);
    if (len == 0)
        return -1;

    *outl = len;
    return 1;
}