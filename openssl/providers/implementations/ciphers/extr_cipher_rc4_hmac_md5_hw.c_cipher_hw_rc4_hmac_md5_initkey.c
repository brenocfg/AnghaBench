#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  ks; } ;
struct TYPE_4__ {int /*<<< orphan*/  payload_length; int /*<<< orphan*/  head; int /*<<< orphan*/  md; int /*<<< orphan*/  tail; TYPE_1__ ks; } ;
typedef  TYPE_2__ PROV_RC4_HMAC_MD5_CTX ;
typedef  int /*<<< orphan*/  PROV_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_PAYLOAD_LENGTH ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int cipher_hw_rc4_hmac_md5_initkey(PROV_CIPHER_CTX *bctx,
                                          const uint8_t *key, size_t keylen)
{
    PROV_RC4_HMAC_MD5_CTX *ctx = (PROV_RC4_HMAC_MD5_CTX *)bctx;

    RC4_set_key(&ctx->ks.ks, keylen, key);
    MD5_Init(&ctx->head);       /* handy when benchmarking */
    ctx->tail = ctx->head;
    ctx->md = ctx->head;
    ctx->payload_length = NO_PAYLOAD_LENGTH;
    return 1;
}