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
typedef  int /*<<< orphan*/  OSSL_CMP_PKIHEADER ;
typedef  int /*<<< orphan*/  OSSL_CMP_ITAV ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 scalar_t__ ASN1_NULL_new () ; 
 int /*<<< orphan*/  ASN1_TYPE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NID_id_it_implicitConfirm ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OSSL_CMP_ITAV_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_CMP_ITAV_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_generalInfo_push0_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ossl_cmp_hdr_set_implicitConfirm(OSSL_CMP_PKIHEADER *hdr)
{
    OSSL_CMP_ITAV *itav;
    ASN1_TYPE *asn1null;

    if (!ossl_assert(hdr != NULL))
        return 0;
    asn1null = (ASN1_TYPE *)ASN1_NULL_new();
    if (asn1null == NULL)
        return 0;
    if ((itav = OSSL_CMP_ITAV_create(OBJ_nid2obj(NID_id_it_implicitConfirm),
                                     asn1null)) == NULL)
        goto err;
    if (!ossl_cmp_hdr_generalInfo_push0_item(hdr, itav))
        goto err;
    return 1;

 err:
    ASN1_TYPE_free(asn1null);
    OSSL_CMP_ITAV_free(itav);
    return 0;
}