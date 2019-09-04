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
struct TYPE_4__ {int pkey_flags; struct TYPE_4__* info; struct TYPE_4__* pem_str; } ;
typedef  TYPE_1__ EVP_PKEY_ASN1_METHOD ;

/* Variables and functions */
 int ASN1_PKEY_DYNAMIC ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void EVP_PKEY_asn1_free(EVP_PKEY_ASN1_METHOD *ameth)
{
    if (ameth && (ameth->pkey_flags & ASN1_PKEY_DYNAMIC)) {
        OPENSSL_free(ameth->pem_str);
        OPENSSL_free(ameth->info);
        OPENSSL_free(ameth);
    }
}