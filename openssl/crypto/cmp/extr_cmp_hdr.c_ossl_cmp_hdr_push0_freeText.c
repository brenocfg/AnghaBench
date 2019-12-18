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
struct TYPE_3__ {int /*<<< orphan*/ * freeText; } ;
typedef  TYPE_1__ OSSL_CMP_PKIHEADER ;
typedef  int /*<<< orphan*/  ASN1_UTF8STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/ * sk_ASN1_UTF8STRING_new_null () ; 
 int sk_ASN1_UTF8STRING_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ossl_cmp_hdr_push0_freeText(OSSL_CMP_PKIHEADER *hdr, ASN1_UTF8STRING *text)
{
    if (!ossl_assert(hdr != NULL && text != NULL))
        return 0;

    if (hdr->freeText == NULL
            && (hdr->freeText = sk_ASN1_UTF8STRING_new_null()) == NULL)
        return 0;

    return sk_ASN1_UTF8STRING_push(hdr->freeText, text);
}