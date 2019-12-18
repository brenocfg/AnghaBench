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
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int ASN1_item_i2d (void*,unsigned char**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_Digest (unsigned char*,int,unsigned char*,unsigned int*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 

int ASN1_item_digest(const ASN1_ITEM *it, const EVP_MD *type, void *asn,
                     unsigned char *md, unsigned int *len)
{
    int i;
    unsigned char *str = NULL;

    i = ASN1_item_i2d(asn, &str, it);
    if (!str)
        return 0;

    if (!EVP_Digest(str, i, md, len, type, NULL)) {
        OPENSSL_free(str);
        return 0;
    }
    OPENSSL_free(str);
    return 1;
}