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
struct TYPE_7__ {int /*<<< orphan*/  blocklen; int /*<<< orphan*/  V; int /*<<< orphan*/  K; } ;
struct TYPE_6__ {TYPE_2__ hmac; } ;
struct TYPE_8__ {TYPE_1__ data; } ;
typedef  TYPE_2__ RAND_DRBG_HMAC ;
typedef  TYPE_3__ RAND_DRBG ;

/* Variables and functions */
 int drbg_hmac_update (TYPE_3__*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drbg_hmac_instantiate(RAND_DRBG *drbg,
                                 const unsigned char *ent, size_t ent_len,
                                 const unsigned char *nonce, size_t nonce_len,
                                 const unsigned char *pstr, size_t pstr_len)
{
    RAND_DRBG_HMAC *hmac = &drbg->data.hmac;

    /* (Step 2) Key = 0x00 00...00 */
    memset(hmac->K, 0x00, hmac->blocklen);
    /* (Step 3) V = 0x01 01...01 */
    memset(hmac->V, 0x01, hmac->blocklen);
    /* (Step 4) (K,V) = HMAC_DRBG_Update(entropy||nonce||pers string, K, V) */
    return drbg_hmac_update(drbg, ent, ent_len, nonce, nonce_len, pstr,
                            pstr_len);
}