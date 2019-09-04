#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  c; } ;
struct TYPE_10__ {TYPE_2__ sum; TYPE_2__ offset; TYPE_2__ checksum; } ;
struct TYPE_12__ {TYPE_1__ sess; int /*<<< orphan*/  keyenc; int /*<<< orphan*/  (* encrypt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_2__ l_dollar; } ;
typedef  TYPE_2__ OCB_BLOCK ;
typedef  TYPE_3__ OCB128_CONTEXT ;

/* Variables and functions */
 int CRYPTO_memcmp (TYPE_2__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  ocb_block16_xor (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocb_finish(OCB128_CONTEXT *ctx, unsigned char *tag, size_t len,
                      int write)
{
    OCB_BLOCK tmp;

    if (len > 16 || len < 1) {
        return -1;
    }

    /*
     * Tag = ENCIPHER(K, Checksum_* xor Offset_* xor L_$) xor HASH(K,A)
     */
    ocb_block16_xor(&ctx->sess.checksum, &ctx->sess.offset, &tmp);
    ocb_block16_xor(&ctx->l_dollar, &tmp, &tmp);
    ctx->encrypt(tmp.c, tmp.c, ctx->keyenc);
    ocb_block16_xor(&tmp, &ctx->sess.sum, &tmp);

    if (write) {
        memcpy(tag, &tmp, len);
        return 1;
    } else {
        return CRYPTO_memcmp(&tmp, tag, len);
    }
}