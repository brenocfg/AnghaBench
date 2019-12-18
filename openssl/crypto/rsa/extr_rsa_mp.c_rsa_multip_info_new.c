#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * pp; int /*<<< orphan*/ * t; int /*<<< orphan*/ * d; int /*<<< orphan*/ * r; } ;
typedef  TYPE_1__ RSA_PRIME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 void* BN_secure_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  RSA_F_RSA_MULTIP_INFO_NEW ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RSA_PRIME_INFO *rsa_multip_info_new(void)
{
    RSA_PRIME_INFO *pinfo;

    /* create a RSA_PRIME_INFO structure */
    if ((pinfo = OPENSSL_zalloc(sizeof(RSA_PRIME_INFO))) == NULL) {
        RSAerr(RSA_F_RSA_MULTIP_INFO_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    if ((pinfo->r = BN_secure_new()) == NULL)
        goto err;
    if ((pinfo->d = BN_secure_new()) == NULL)
        goto err;
    if ((pinfo->t = BN_secure_new()) == NULL)
        goto err;
    if ((pinfo->pp = BN_secure_new()) == NULL)
        goto err;

    return pinfo;

 err:
    BN_free(pinfo->r);
    BN_free(pinfo->d);
    BN_free(pinfo->t);
    BN_free(pinfo->pp);
    OPENSSL_free(pinfo);
    return NULL;
}