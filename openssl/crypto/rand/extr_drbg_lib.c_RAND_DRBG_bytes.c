#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; size_t max_request; int /*<<< orphan*/ * adin_pool; int /*<<< orphan*/  max_adinlen; } ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */
 size_t RAND_DRBG_generate (TYPE_1__*,unsigned char*,size_t,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  rand_drbg_cleanup_additional_data (int /*<<< orphan*/ *,unsigned char*) ; 
 size_t rand_drbg_get_additional_data (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/ * rand_pool_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int RAND_DRBG_bytes(RAND_DRBG *drbg, unsigned char *out, size_t outlen)
{
    unsigned char *additional = NULL;
    size_t additional_len;
    size_t chunk;
    size_t ret = 0;

    if (drbg->adin_pool == NULL) {
        if (drbg->type == 0)
            goto err;
        drbg->adin_pool = rand_pool_new(0, 0, 0, drbg->max_adinlen);
        if (drbg->adin_pool == NULL)
            goto err;
    }

    additional_len = rand_drbg_get_additional_data(drbg->adin_pool,
                                                   &additional);

    for ( ; outlen > 0; outlen -= chunk, out += chunk) {
        chunk = outlen;
        if (chunk > drbg->max_request)
            chunk = drbg->max_request;
        ret = RAND_DRBG_generate(drbg, out, chunk, 0, additional, additional_len);
        if (!ret)
            goto err;
    }
    ret = 1;

 err:
    if (additional != NULL)
        rand_drbg_cleanup_additional_data(drbg->adin_pool, additional);

    return ret;
}