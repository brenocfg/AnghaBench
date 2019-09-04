#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int (* pkey_asn1_meths ) (TYPE_2__*,TYPE_1__ const**,int const**,int const) ;} ;
struct TYPE_9__ {char const* pem_str; } ;
typedef  TYPE_1__ const EVP_PKEY_ASN1_METHOD ;
typedef  TYPE_2__ ENGINE ;

/* Variables and functions */
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,int) ; 
 int stub1 (TYPE_2__*,TYPE_1__ const**,int const**,int const) ; 
 int stub2 (TYPE_2__*,TYPE_1__ const**,int const**,int const) ; 

const EVP_PKEY_ASN1_METHOD *ENGINE_get_pkey_asn1_meth_str(ENGINE *e,
                                                          const char *str,
                                                          int len)
{
    int i, nidcount;
    const int *nids;
    EVP_PKEY_ASN1_METHOD *ameth;
    if (!e->pkey_asn1_meths)
        return NULL;
    if (len == -1)
        len = strlen(str);
    nidcount = e->pkey_asn1_meths(e, NULL, &nids, 0);
    for (i = 0; i < nidcount; i++) {
        e->pkey_asn1_meths(e, &ameth, NULL, nids[i]);
        if (((int)strlen(ameth->pem_str) == len)
            && strncasecmp(ameth->pem_str, str, len) == 0)
            return ameth;
    }
    return NULL;
}