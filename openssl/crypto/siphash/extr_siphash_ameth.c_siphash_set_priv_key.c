#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_5__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 size_t SIPHASH_KEY_SIZE ; 

__attribute__((used)) static int siphash_set_priv_key(EVP_PKEY *pkey, const unsigned char *priv,
                                size_t len)
{
    ASN1_OCTET_STRING *os;

    if (pkey->pkey.ptr != NULL || len != SIPHASH_KEY_SIZE)
        return 0;

    os = ASN1_OCTET_STRING_new();
    if (os == NULL)
        return 0;

    if (!ASN1_OCTET_STRING_set(os, priv, len)) {
        ASN1_OCTET_STRING_free(os);
        return 0;
    }

    pkey->pkey.ptr = os;
    return 1;
}