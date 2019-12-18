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
typedef  int /*<<< orphan*/  PROV_GCM_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_OUTPUT_BUFFER_TOO_SMALL ; 
 scalar_t__ gcm_cipher_internal (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char const*,size_t) ; 

int gcm_cipher(void *vctx,
               unsigned char *out, size_t *outl, size_t outsize,
               const unsigned char *in, size_t inl)
{
    PROV_GCM_CTX *ctx = (PROV_GCM_CTX *)vctx;

    if (outsize < inl) {
        ERR_raise(ERR_LIB_PROV, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
        return 0;
    }

    if (gcm_cipher_internal(ctx, out, outl, in, inl) <= 0)
        return 0;

    *outl = inl;
    return 1;
}