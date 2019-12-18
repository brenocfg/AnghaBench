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
struct TYPE_5__ {TYPE_1__* public_key; int /*<<< orphan*/  algor; } ;
typedef  TYPE_2__ X509_PUBKEY ;
struct TYPE_4__ {unsigned char* data; int length; int flags; } ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int ASN1_STRING_FLAG_BITS_LEFT ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*) ; 

int X509_PUBKEY_set0_param(X509_PUBKEY *pub, ASN1_OBJECT *aobj,
                           int ptype, void *pval,
                           unsigned char *penc, int penclen)
{
    if (!X509_ALGOR_set0(pub->algor, aobj, ptype, pval))
        return 0;
    if (penc) {
        OPENSSL_free(pub->public_key->data);
        pub->public_key->data = penc;
        pub->public_key->length = penclen;
        /* Set number of unused bits to zero */
        pub->public_key->flags &= ~(ASN1_STRING_FLAG_BITS_LEFT | 0x07);
        pub->public_key->flags |= ASN1_STRING_FLAG_BITS_LEFT;
    }
    return 1;
}