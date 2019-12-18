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
struct TYPE_4__ {size_t md_size; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_1__ EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_MD_SIZE ; 
 int /*<<< orphan*/  EVP_R_MESSAGE_DIGEST_IS_NULL ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_DIGEST_PARAM_SIZE ; 
 int /*<<< orphan*/  OSSL_PARAM_END ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_size_t (int /*<<< orphan*/ ,size_t*) ; 
 int evp_do_md_getparams (TYPE_1__ const*,int /*<<< orphan*/ *) ; 

int EVP_MD_size(const EVP_MD *md)
{
    int ok;
    size_t v = md->md_size;
    OSSL_PARAM params[2] = { OSSL_PARAM_END, OSSL_PARAM_END };

    if (md == NULL) {
        EVPerr(EVP_F_EVP_MD_SIZE, EVP_R_MESSAGE_DIGEST_IS_NULL);
        return -1;
    }

    params[0] = OSSL_PARAM_construct_size_t(OSSL_DIGEST_PARAM_SIZE, &v);
    ok = evp_do_md_getparams(md, params);

    return ok != 0 ? (int)v : -1;
}