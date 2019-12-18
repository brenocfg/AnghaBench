#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int pkey_id; } ;
typedef  TYPE_1__ EVP_PKEY_ASN1_METHOD ;

/* Variables and functions */
 TYPE_1__** OBJ_bsearch_ameth (TYPE_1__ const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 scalar_t__ app_methods ; 
 int sk_EVP_PKEY_ASN1_METHOD_find (scalar_t__,TYPE_1__*) ; 
 TYPE_1__ const* sk_EVP_PKEY_ASN1_METHOD_value (scalar_t__,int) ; 
 int /*<<< orphan*/  standard_methods ; 

__attribute__((used)) static const EVP_PKEY_ASN1_METHOD *pkey_asn1_find(int type)
{
    EVP_PKEY_ASN1_METHOD tmp;
    const EVP_PKEY_ASN1_METHOD *t = &tmp, **ret;

    tmp.pkey_id = type;
    if (app_methods) {
        int idx;
        idx = sk_EVP_PKEY_ASN1_METHOD_find(app_methods, &tmp);
        if (idx >= 0)
            return sk_EVP_PKEY_ASN1_METHOD_value(app_methods, idx);
    }
    ret = OBJ_bsearch_ameth(&t, standard_methods, OSSL_NELEM(standard_methods));
    if (ret == NULL || *ret == NULL)
        return NULL;
    return *ret;
}