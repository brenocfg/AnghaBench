#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int len; int /*<<< orphan*/  enc; scalar_t__ modified; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;
typedef  TYPE_1__ ASN1_ENCODING ;

/* Variables and functions */
 TYPE_1__* asn1_get_const_enc_ptr (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 

int asn1_enc_restore(int *len, unsigned char **out, const ASN1_VALUE **pval,
                     const ASN1_ITEM *it)
{
    const ASN1_ENCODING *enc = asn1_get_const_enc_ptr(pval, it);

    if (enc == NULL || enc->modified)
        return 0;
    if (out) {
        memcpy(*out, enc->enc, enc->len);
        *out += enc->len;
    }
    if (len != NULL)
        *len = enc->len;
    return 1;
}