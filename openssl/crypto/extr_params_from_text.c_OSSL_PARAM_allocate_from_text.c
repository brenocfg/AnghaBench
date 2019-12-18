#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (void*) ; 
 void* OPENSSL_zalloc (size_t) ; 
 int construct_from_text (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,size_t,int,void*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_from_text (int /*<<< orphan*/  const*,char const*,char const*,size_t,int /*<<< orphan*/  const**,int*,size_t*,int /*<<< orphan*/ **) ; 

int OSSL_PARAM_allocate_from_text(OSSL_PARAM *to,
                                  const OSSL_PARAM *paramdefs,
                                  const char *key, const char *value,
                                  size_t value_n)
{
    const OSSL_PARAM *paramdef = NULL;
    int ishex = 0;
    void *buf = NULL;
    size_t buf_n = 0;
    BIGNUM *tmpbn = NULL;
    int ok = 0;

    if (to == NULL || paramdefs == NULL)
        return 0;

    if (!prepare_from_text(paramdefs, key, value, value_n,
                           &paramdef, &ishex, &buf_n, &tmpbn))
        return 0;

    if ((buf = OPENSSL_zalloc(buf_n > 0 ? buf_n : 1)) == NULL) {
        CRYPTOerr(0, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    ok = construct_from_text(to, paramdef, value, value_n, ishex,
                             buf, buf_n, tmpbn);
    BN_free(tmpbn);
    if (!ok)
        OPENSSL_free(buf);
    return ok;
}