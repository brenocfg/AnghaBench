#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int blocklen; int /*<<< orphan*/  const* md; int /*<<< orphan*/ * ctx; } ;
struct TYPE_5__ {TYPE_2__ hmac; } ;
struct TYPE_7__ {int strength; int seedlen; int min_entropylen; int min_noncelen; int max_request; void* max_adinlen; void* max_perslen; void* max_noncelen; void* max_entropylen; int /*<<< orphan*/ * meth; int /*<<< orphan*/  type; TYPE_1__ data; } ;
typedef  TYPE_2__ RAND_DRBG_HMAC ;
typedef  TYPE_3__ RAND_DRBG ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 void* DRBG_MAX_LENGTH ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_get_digestbynid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  drbg_hmac_meth ; 

int drbg_hmac_init(RAND_DRBG *drbg)
{
    const EVP_MD *md = NULL;
    RAND_DRBG_HMAC *hmac = &drbg->data.hmac;

    /* Any approved digest is allowed - assume we pass digest (not NID_hmac*) */
    md = EVP_get_digestbynid(drbg->type);
    if (md == NULL)
        return 0;

    drbg->meth = &drbg_hmac_meth;

    if (hmac->ctx == NULL) {
        hmac->ctx = HMAC_CTX_new();
        if (hmac->ctx == NULL)
            return 0;
    }

    /* These are taken from SP 800-90 10.1 Table 2 */
    hmac->md = md;
    hmac->blocklen = EVP_MD_size(md);
    /* See SP800-57 Part1 Rev4 5.6.1 Table 3 */
    drbg->strength = 64 * (int)(hmac->blocklen >> 3);
    if (drbg->strength > 256)
        drbg->strength = 256;
    drbg->seedlen = hmac->blocklen;

    drbg->min_entropylen = drbg->strength / 8;
    drbg->max_entropylen = DRBG_MAX_LENGTH;

    drbg->min_noncelen = drbg->min_entropylen / 2;
    drbg->max_noncelen = DRBG_MAX_LENGTH;

    drbg->max_perslen = DRBG_MAX_LENGTH;
    drbg->max_adinlen = DRBG_MAX_LENGTH;

    /* Maximum number of bits per request = 2^19 = 2^16 bytes*/
    drbg->max_request = 1 << 16;

    return 1;
}