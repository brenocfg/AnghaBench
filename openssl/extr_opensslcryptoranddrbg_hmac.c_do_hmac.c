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
struct TYPE_3__ {unsigned char const* K; size_t blocklen; unsigned char const* V; int /*<<< orphan*/  md; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ RAND_DRBG_HMAC ;
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 scalar_t__ HMAC_Final (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ HMAC_Init_ex (int /*<<< orphan*/ *,unsigned char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HMAC_Update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

__attribute__((used)) static int do_hmac(RAND_DRBG_HMAC *hmac, unsigned char inbyte,
                   const unsigned char *in1, size_t in1len,
                   const unsigned char *in2, size_t in2len,
                   const unsigned char *in3, size_t in3len)
{
    HMAC_CTX *ctx = hmac->ctx;

    return HMAC_Init_ex(ctx, hmac->K, hmac->blocklen, hmac->md, NULL)
           /* K = HMAC(K, V || inbyte || [in1] || [in2] || [in3]) */
           && HMAC_Update(ctx, hmac->V, hmac->blocklen)
           && HMAC_Update(ctx, &inbyte, 1)
           && (in1 == NULL || in1len == 0 || HMAC_Update(ctx, in1, in1len))
           && (in2 == NULL || in2len == 0 || HMAC_Update(ctx, in2, in2len))
           && (in3 == NULL || in3len == 0 || HMAC_Update(ctx, in3, in3len))
           && HMAC_Final(ctx, hmac->K, NULL)
           /* V = HMAC(K, V) */
           && HMAC_Init_ex(ctx, hmac->K, hmac->blocklen, hmac->md, NULL)
           && HMAC_Update(ctx, hmac->V, hmac->blocklen)
           && HMAC_Final(ctx, hmac->V, NULL);
}