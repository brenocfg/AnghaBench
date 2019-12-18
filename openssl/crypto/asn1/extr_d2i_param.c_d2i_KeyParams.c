#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* ameth; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* param_decode ) (TYPE_2__*,unsigned char const**,long) ;} ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_D2I_KEYPARAMS ; 
 int /*<<< orphan*/  ASN1_R_UNSUPPORTED_TYPE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_2__*) ; 
 int EVP_PKEY_id (TYPE_2__*) ; 
 TYPE_2__* EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set_type (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char const**,long) ; 

EVP_PKEY *d2i_KeyParams(int type, EVP_PKEY **a, const unsigned char **pp,
                        long length)
{
    EVP_PKEY *ret = NULL;
    const unsigned char *p = *pp;

    if ((a == NULL) || (*a == NULL)) {
        if ((ret = EVP_PKEY_new()) == NULL)
            return NULL;
    } else
        ret = *a;

    if (type != EVP_PKEY_id(ret) && !EVP_PKEY_set_type(ret, type))
        goto err;

    if (ret->ameth == NULL || ret->ameth->param_decode == NULL) {
        ASN1err(ASN1_F_D2I_KEYPARAMS, ASN1_R_UNSUPPORTED_TYPE);
        goto err;
    }

    if (!ret->ameth->param_decode(ret, &p, length))
        goto err;

    if (a != NULL)
        (*a) = ret;
    return ret;
err:
    if (a == NULL || *a != ret)
        EVP_PKEY_free(ret);
    return NULL;
}