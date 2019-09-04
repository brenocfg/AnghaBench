#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* V; size_t blocklen; int /*<<< orphan*/  md; int /*<<< orphan*/  K; int /*<<< orphan*/ * ctx; } ;
struct TYPE_6__ {TYPE_2__ hmac; } ;
struct TYPE_8__ {TYPE_1__ data; } ;
typedef  TYPE_2__ RAND_DRBG_HMAC ;
typedef  TYPE_3__ RAND_DRBG ;
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  drbg_hmac_update (TYPE_3__*,unsigned char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int drbg_hmac_generate(RAND_DRBG *drbg,
                              unsigned char *out, size_t outlen,
                              const unsigned char *adin, size_t adin_len)
{
    RAND_DRBG_HMAC *hmac = &drbg->data.hmac;
    HMAC_CTX *ctx = hmac->ctx;
    const unsigned char *temp = hmac->V;

    /* (Step 2) if adin != NULL then (K,V) = HMAC_DRBG_Update(adin, K, V) */
    if (adin != NULL
            && adin_len > 0
            && !drbg_hmac_update(drbg, adin, adin_len, NULL, 0, NULL, 0))
        return 0;

    /*
     * (Steps 3-5) temp = NULL
     *             while (len(temp) < outlen) {
     *                 V = HMAC(K, V)
     *                 temp = temp || V
     *             }
     */
    for (;;) {
        if (!HMAC_Init_ex(ctx, hmac->K, hmac->blocklen, hmac->md, NULL)
                || !HMAC_Update(ctx, temp, hmac->blocklen))
            return 0;

        if (outlen > hmac->blocklen) {
            if (!HMAC_Final(ctx, out, NULL))
                return 0;
            temp = out;
        } else {
            if (!HMAC_Final(ctx, hmac->V, NULL))
                return 0;
            memcpy(out, hmac->V, outlen);
            break;
        }
        out += hmac->blocklen;
        outlen -= hmac->blocklen;
    }
    /* (Step 6) (K,V) = HMAC_DRBG_Update(adin, K, V) */
    if (!drbg_hmac_update(drbg, adin, adin_len, NULL, 0, NULL, 0))
        return 0;

    return 1;
}