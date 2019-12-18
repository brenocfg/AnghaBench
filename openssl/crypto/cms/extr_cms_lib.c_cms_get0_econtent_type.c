#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/ * eContentType; } ;
struct TYPE_28__ {TYPE_7__* encryptedContentInfo; } ;
struct TYPE_27__ {int /*<<< orphan*/ * contentType; } ;
struct TYPE_26__ {TYPE_5__* encapContentInfo; } ;
struct TYPE_25__ {int /*<<< orphan*/ * eContentType; } ;
struct TYPE_24__ {TYPE_3__* encryptedContentInfo; } ;
struct TYPE_23__ {int /*<<< orphan*/ * contentType; } ;
struct TYPE_22__ {TYPE_1__* encapContentInfo; } ;
struct TYPE_21__ {int /*<<< orphan*/ * eContentType; } ;
struct TYPE_19__ {TYPE_12__* compressedData; TYPE_10__* authenticatedData; TYPE_8__* encryptedData; TYPE_6__* digestedData; TYPE_4__* envelopedData; TYPE_2__* signedData; } ;
struct TYPE_20__ {TYPE_13__ d; int /*<<< orphan*/  contentType; } ;
struct TYPE_18__ {TYPE_11__* encapContentInfo; } ;
struct TYPE_17__ {int /*<<< orphan*/ * eContentType; } ;
struct TYPE_16__ {TYPE_9__* encapContentInfo; } ;
typedef  TYPE_14__ CMS_ContentInfo ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_GET0_ECONTENT_TYPE ; 
 int /*<<< orphan*/  CMS_R_UNSUPPORTED_CONTENT_TYPE ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NID_id_smime_ct_authData 133 
#define  NID_id_smime_ct_compressedData 132 
#define  NID_pkcs7_digest 131 
#define  NID_pkcs7_encrypted 130 
#define  NID_pkcs7_enveloped 129 
#define  NID_pkcs7_signed 128 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ASN1_OBJECT **cms_get0_econtent_type(CMS_ContentInfo *cms)
{
    switch (OBJ_obj2nid(cms->contentType)) {

    case NID_pkcs7_signed:
        return &cms->d.signedData->encapContentInfo->eContentType;

    case NID_pkcs7_enveloped:
        return &cms->d.envelopedData->encryptedContentInfo->contentType;

    case NID_pkcs7_digest:
        return &cms->d.digestedData->encapContentInfo->eContentType;

    case NID_pkcs7_encrypted:
        return &cms->d.encryptedData->encryptedContentInfo->contentType;

    case NID_id_smime_ct_authData:
        return &cms->d.authenticatedData->encapContentInfo->eContentType;

    case NID_id_smime_ct_compressedData:
        return &cms->d.compressedData->encapContentInfo->eContentType;

    default:
        CMSerr(CMS_F_CMS_GET0_ECONTENT_TYPE, CMS_R_UNSUPPORTED_CONTENT_TYPE);
        return NULL;

    }
}