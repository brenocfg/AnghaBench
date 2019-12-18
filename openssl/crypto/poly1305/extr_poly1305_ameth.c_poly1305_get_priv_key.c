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
struct TYPE_4__ {scalar_t__ ptr; } ;
struct TYPE_5__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 size_t POLY1305_KEY_SIZE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int poly1305_get_priv_key(const EVP_PKEY *pkey, unsigned char *priv,
                                 size_t *len)
{
    ASN1_OCTET_STRING *os = (ASN1_OCTET_STRING *)pkey->pkey.ptr;

    if (priv == NULL) {
        *len = POLY1305_KEY_SIZE;
        return 1;
    }

    if (os == NULL || *len < POLY1305_KEY_SIZE)
        return 0;

    memcpy(priv, ASN1_STRING_get0_data(os), ASN1_STRING_length(os));
    *len = POLY1305_KEY_SIZE;

    return 1;
}