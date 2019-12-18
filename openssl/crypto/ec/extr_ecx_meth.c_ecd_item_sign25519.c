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
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  NID_ED25519 ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_UNDEF ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ecd_item_sign25519(EVP_MD_CTX *ctx, const ASN1_ITEM *it, void *asn,
                              X509_ALGOR *alg1, X509_ALGOR *alg2,
                              ASN1_BIT_STRING *str)
{
    /* Set algorithms identifiers */
    X509_ALGOR_set0(alg1, OBJ_nid2obj(NID_ED25519), V_ASN1_UNDEF, NULL);
    if (alg2)
        X509_ALGOR_set0(alg2, OBJ_nid2obj(NID_ED25519), V_ASN1_UNDEF, NULL);
    /* Algorithm identifiers set: carry on as normal */
    return 3;
}