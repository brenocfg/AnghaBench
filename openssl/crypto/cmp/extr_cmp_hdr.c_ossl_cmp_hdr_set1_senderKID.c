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
struct TYPE_3__ {int /*<<< orphan*/  senderKID; } ;
typedef  TYPE_1__ OSSL_CMP_PKIHEADER ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 
 int ossl_cmp_asn1_octet_string_set1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int ossl_cmp_hdr_set1_senderKID(OSSL_CMP_PKIHEADER *hdr,
                                const ASN1_OCTET_STRING *senderKID)
{
    if (!ossl_assert(hdr != NULL))
        return 0;
    return ossl_cmp_asn1_octet_string_set1(&hdr->senderKID, senderKID);
}