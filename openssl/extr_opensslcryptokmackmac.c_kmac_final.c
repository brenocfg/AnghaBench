#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int out_len; scalar_t__ xof_mode; int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 scalar_t__ EVP_DigestFinalXOF (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int KMAC_MAX_ENCODED_HEADER_LEN ; 
 scalar_t__ right_encode (unsigned char*,int*,int) ; 

__attribute__((used)) static int kmac_final(EVP_MAC_IMPL *kctx, unsigned char *out)
{
    EVP_MD_CTX *ctx = kctx->ctx;
    int lbits, len;
    unsigned char encoded_outlen[KMAC_MAX_ENCODED_HEADER_LEN];

    /* KMAC XOF mode sets the encoded length to 0 */
    lbits = (kctx->xof_mode ? 0 : (kctx->out_len * 8));

    return right_encode(encoded_outlen, &len, lbits)
           && EVP_DigestUpdate(ctx, encoded_outlen, len)
           && EVP_DigestFinalXOF(ctx, out, kctx->out_len);
}