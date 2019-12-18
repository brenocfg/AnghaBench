#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* mdname; int /*<<< orphan*/  mdsize; int /*<<< orphan*/ * md; } ;
typedef  TYPE_1__ PROV_DSA_CTX ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_PARAM_get_size_t (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_utf8_string (int /*<<< orphan*/  const*,char**,int) ; 
 int /*<<< orphan*/ * OSSL_PARAM_locate_const (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_SIGNATURE_PARAM_DIGEST ; 
 int /*<<< orphan*/  OSSL_SIGNATURE_PARAM_DIGEST_SIZE ; 

__attribute__((used)) static int dsa_set_ctx_params(void *vpdsactx, const OSSL_PARAM params[])
{
    PROV_DSA_CTX *pdsactx = (PROV_DSA_CTX *)vpdsactx;
    const OSSL_PARAM *p;
    char *mdname;

    if (pdsactx == NULL || params == NULL)
        return 0;

    if (pdsactx->md != NULL) {
        /*
         * You cannot set the digest name/size when doing a DigestSign or
         * DigestVerify.
         */
        return 1;
    }

    p = OSSL_PARAM_locate_const(params, OSSL_SIGNATURE_PARAM_DIGEST_SIZE);
    if (p != NULL && !OSSL_PARAM_get_size_t(p, &pdsactx->mdsize))
        return 0;

    /*
     * We never actually use the mdname, but we do support getting it later.
     * This can be useful for applications that want to know the MD that they
     * previously set.
     */
    p = OSSL_PARAM_locate_const(params, OSSL_SIGNATURE_PARAM_DIGEST);
    mdname = pdsactx->mdname;
    if (p != NULL
            && !OSSL_PARAM_get_utf8_string(p, &mdname, sizeof(pdsactx->mdname)))
        return 0;

    return 1;
}