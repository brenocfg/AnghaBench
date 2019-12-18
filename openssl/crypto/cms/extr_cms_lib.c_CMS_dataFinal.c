#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  contentType; } ;
typedef  TYPE_1__ CMS_ContentInfo ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_2__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int ASN1_STRING_FLAG_CONT ; 
 int /*<<< orphan*/  ASN1_STRING_set0 (TYPE_2__*,unsigned char*,long) ; 
 int /*<<< orphan*/  BIO_FLAGS_MEM_RDONLY ; 
 int /*<<< orphan*/  BIO_TYPE_MEM ; 
 int /*<<< orphan*/ * BIO_find_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long BIO_get_mem_data (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  BIO_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_mem_eof_return (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMS_F_CMS_DATAFINAL ; 
 int /*<<< orphan*/  CMS_R_CONTENT_NOT_FOUND ; 
 int /*<<< orphan*/  CMS_R_UNSUPPORTED_TYPE ; 
 TYPE_2__** CMS_get0_content (TYPE_1__*) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NID_id_smime_ct_compressedData 133 
#define  NID_pkcs7_data 132 
#define  NID_pkcs7_digest 131 
#define  NID_pkcs7_encrypted 130 
#define  NID_pkcs7_enveloped 129 
#define  NID_pkcs7_signed 128 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int cms_DigestedData_do_final (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cms_SignedData_final (TYPE_1__*,int /*<<< orphan*/ *) ; 

int CMS_dataFinal(CMS_ContentInfo *cms, BIO *cmsbio)
{
    ASN1_OCTET_STRING **pos = CMS_get0_content(cms);

    if (pos == NULL)
        return 0;
    /* If embedded content find memory BIO and set content */
    if (*pos && ((*pos)->flags & ASN1_STRING_FLAG_CONT)) {
        BIO *mbio;
        unsigned char *cont;
        long contlen;
        mbio = BIO_find_type(cmsbio, BIO_TYPE_MEM);
        if (!mbio) {
            CMSerr(CMS_F_CMS_DATAFINAL, CMS_R_CONTENT_NOT_FOUND);
            return 0;
        }
        contlen = BIO_get_mem_data(mbio, &cont);
        /* Set bio as read only so its content can't be clobbered */
        BIO_set_flags(mbio, BIO_FLAGS_MEM_RDONLY);
        BIO_set_mem_eof_return(mbio, 0);
        ASN1_STRING_set0(*pos, cont, contlen);
        (*pos)->flags &= ~ASN1_STRING_FLAG_CONT;
    }

    switch (OBJ_obj2nid(cms->contentType)) {

    case NID_pkcs7_data:
    case NID_pkcs7_enveloped:
    case NID_pkcs7_encrypted:
    case NID_id_smime_ct_compressedData:
        /* Nothing to do */
        return 1;

    case NID_pkcs7_signed:
        return cms_SignedData_final(cms, cmsbio);

    case NID_pkcs7_digest:
        return cms_DigestedData_do_final(cms, cmsbio, 0);

    default:
        CMSerr(CMS_F_CMS_DATAFINAL, CMS_R_UNSUPPORTED_TYPE);
        return 0;
    }
}