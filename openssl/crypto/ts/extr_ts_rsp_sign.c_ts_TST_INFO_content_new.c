#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * other; } ;
struct TYPE_9__ {TYPE_1__ d; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ PKCS7 ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/ * ASN1_TYPE_new () ; 
 int /*<<< orphan*/  ASN1_TYPE_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NID_id_smime_ct_TSTInfo ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7_free (TYPE_2__*) ; 
 TYPE_2__* PKCS7_new () ; 
 int /*<<< orphan*/  PKCS7_set_content (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 

__attribute__((used)) static int ts_TST_INFO_content_new(PKCS7 *p7)
{
    PKCS7 *ret = NULL;
    ASN1_OCTET_STRING *octet_string = NULL;

    /* Create new encapsulated NID_id_smime_ct_TSTInfo content. */
    if ((ret = PKCS7_new()) == NULL)
        goto err;
    if ((ret->d.other = ASN1_TYPE_new()) == NULL)
        goto err;
    ret->type = OBJ_nid2obj(NID_id_smime_ct_TSTInfo);
    if ((octet_string = ASN1_OCTET_STRING_new()) == NULL)
        goto err;
    ASN1_TYPE_set(ret->d.other, V_ASN1_OCTET_STRING, octet_string);
    octet_string = NULL;

    /* Add encapsulated content to signed PKCS7 structure. */
    if (!PKCS7_set_content(p7, ret))
        goto err;

    return 1;
 err:
    ASN1_OCTET_STRING_free(octet_string);
    PKCS7_free(ret);
    return 0;
}