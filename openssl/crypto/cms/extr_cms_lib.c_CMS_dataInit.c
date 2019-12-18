#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  contentType; } ;
typedef  TYPE_1__ CMS_ContentInfo ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMS_F_CMS_DATAINIT ; 
 int /*<<< orphan*/  CMS_R_NO_CONTENT ; 
 int /*<<< orphan*/  CMS_R_UNSUPPORTED_TYPE ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NID_id_smime_ct_compressedData 133 
#define  NID_pkcs7_data 132 
#define  NID_pkcs7_digest 131 
#define  NID_pkcs7_encrypted 130 
#define  NID_pkcs7_enveloped 129 
#define  NID_pkcs7_signed 128 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cms_CompressedData_init_bio (TYPE_1__*) ; 
 int /*<<< orphan*/ * cms_DigestedData_init_bio (TYPE_1__*) ; 
 int /*<<< orphan*/ * cms_EncryptedData_init_bio (TYPE_1__*) ; 
 int /*<<< orphan*/ * cms_EnvelopedData_init_bio (TYPE_1__*) ; 
 int /*<<< orphan*/ * cms_SignedData_init_bio (TYPE_1__*) ; 
 int /*<<< orphan*/ * cms_content_bio (TYPE_1__*) ; 

BIO *CMS_dataInit(CMS_ContentInfo *cms, BIO *icont)
{
    BIO *cmsbio, *cont;
    if (icont)
        cont = icont;
    else
        cont = cms_content_bio(cms);
    if (!cont) {
        CMSerr(CMS_F_CMS_DATAINIT, CMS_R_NO_CONTENT);
        return NULL;
    }
    switch (OBJ_obj2nid(cms->contentType)) {

    case NID_pkcs7_data:
        return cont;

    case NID_pkcs7_signed:
        cmsbio = cms_SignedData_init_bio(cms);
        break;

    case NID_pkcs7_digest:
        cmsbio = cms_DigestedData_init_bio(cms);
        break;
#ifdef ZLIB
    case NID_id_smime_ct_compressedData:
        cmsbio = cms_CompressedData_init_bio(cms);
        break;
#endif

    case NID_pkcs7_encrypted:
        cmsbio = cms_EncryptedData_init_bio(cms);
        break;

    case NID_pkcs7_enveloped:
        cmsbio = cms_EnvelopedData_init_bio(cms);
        break;

    default:
        CMSerr(CMS_F_CMS_DATAINIT, CMS_R_UNSUPPORTED_TYPE);
        return NULL;
    }

    if (cmsbio)
        return BIO_push(cmsbio, cont);

    if (!icont)
        BIO_free(cont);
    return NULL;

}