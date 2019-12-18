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
struct TYPE_5__ {int pkey_base_id; } ;
typedef  TYPE_1__ EVP_PKEY_ASN1_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_PKEY_ALIAS ; 
 int /*<<< orphan*/  EVP_PKEY_asn1_add0 (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_PKEY_asn1_free (TYPE_1__*) ; 
 TYPE_1__* EVP_PKEY_asn1_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int EVP_PKEY_asn1_add_alias(int to, int from)
{
    EVP_PKEY_ASN1_METHOD *ameth;
    ameth = EVP_PKEY_asn1_new(from, ASN1_PKEY_ALIAS, NULL, NULL);
    if (ameth == NULL)
        return 0;
    ameth->pkey_base_id = to;
    if (!EVP_PKEY_asn1_add0(ameth)) {
        EVP_PKEY_asn1_free(ameth);
        return 0;
    }
    return 1;
}