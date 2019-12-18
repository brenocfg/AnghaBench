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
struct TYPE_6__ {int blocklen; int /*<<< orphan*/ * md; int /*<<< orphan*/ * ctx; } ;
struct TYPE_5__ {TYPE_2__ hash; } ;
struct TYPE_7__ {int strength; int min_entropylen; int min_noncelen; int max_request; void* max_adinlen; void* max_perslen; void* max_noncelen; void* max_entropylen; int /*<<< orphan*/  seedlen; int /*<<< orphan*/ * meth; int /*<<< orphan*/  type; int /*<<< orphan*/  libctx; TYPE_1__ data; } ;
typedef  TYPE_2__ RAND_DRBG_HASH ;
typedef  TYPE_3__ RAND_DRBG ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 void* DRBG_MAX_LENGTH ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int EVP_MD_FLAG_XOF ; 
 int /*<<< orphan*/ * EVP_MD_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int EVP_MD_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_free (int /*<<< orphan*/ *) ; 
 int EVP_MD_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HASH_PRNG_MAX_SEEDLEN ; 
 int /*<<< orphan*/  HASH_PRNG_SMALL_SEEDLEN ; 
 int MAX_BLOCKLEN_USING_SMALL_SEEDLEN ; 
 int /*<<< orphan*/  drbg_hash_meth ; 
 int /*<<< orphan*/  ossl_prov_util_nid_to_name (int /*<<< orphan*/ ) ; 

int drbg_hash_init(RAND_DRBG *drbg)
{
    EVP_MD *md;
    RAND_DRBG_HASH *hash = &drbg->data.hash;

    /*
     * Confirm digest is allowed. We allow all digests that are not XOF
     * (such as SHAKE).  In FIPS mode, the fetch will fail for non-approved
     * digests.
     */
    md = EVP_MD_fetch(drbg->libctx, ossl_prov_util_nid_to_name(drbg->type), "");
    if (md == NULL)
        return 0;

    if ((EVP_MD_flags(md) & EVP_MD_FLAG_XOF) != 0)
        return 0;

    drbg->meth = &drbg_hash_meth;

    if (hash->ctx == NULL) {
        hash->ctx = EVP_MD_CTX_new();
        if (hash->ctx == NULL) {
            EVP_MD_free(md);
            return 0;
        }
    }

    EVP_MD_free(hash->md);
    hash->md = md;

    /* These are taken from SP 800-90 10.1 Table 2 */
    hash->blocklen = EVP_MD_size(md);
    /* See SP800-57 Part1 Rev4 5.6.1 Table 3 */
    drbg->strength = 64 * (hash->blocklen >> 3);
    if (drbg->strength > 256)
        drbg->strength = 256;
    if (hash->blocklen > MAX_BLOCKLEN_USING_SMALL_SEEDLEN)
        drbg->seedlen = HASH_PRNG_MAX_SEEDLEN;
    else
        drbg->seedlen = HASH_PRNG_SMALL_SEEDLEN;

    drbg->min_entropylen = drbg->strength / 8;
    drbg->max_entropylen = DRBG_MAX_LENGTH;

    drbg->min_noncelen = drbg->min_entropylen / 2;
    drbg->max_noncelen = DRBG_MAX_LENGTH;

    drbg->max_perslen = DRBG_MAX_LENGTH;
    drbg->max_adinlen = DRBG_MAX_LENGTH;

    /* Maximum number of bits per request = 2^19  = 2^16 bytes */
    drbg->max_request = 1 << 16;

    return 1;
}