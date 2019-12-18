#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_9__ {TYPE_8__* parameter; int /*<<< orphan*/ * algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
struct TYPE_12__ {int /*<<< orphan*/  type; } ;
struct TYPE_11__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int /*<<< orphan*/  serialNumber; int /*<<< orphan*/  issuerKeyHash; int /*<<< orphan*/  issuerNameHash; TYPE_1__ hashAlgorithm; } ;
typedef  TYPE_2__ OCSP_CERTID ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  TYPE_3__ ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 scalar_t__ ASN1_STRING_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 TYPE_8__* ASN1_TYPE_new () ; 
 int /*<<< orphan*/  EVP_Digest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned int*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int EVP_MAX_MD_SIZE ; 
 int EVP_MD_type (int /*<<< orphan*/  const*) ; 
 int NID_undef ; 
 int /*<<< orphan*/ * OBJ_nid2obj (int) ; 
 int /*<<< orphan*/  OCSP_CERTID_free (TYPE_2__*) ; 
 TYPE_2__* OCSP_CERTID_new () ; 
 int /*<<< orphan*/  OCSP_F_OCSP_CERT_ID_NEW ; 
 int /*<<< orphan*/  OCSP_R_DIGEST_ERR ; 
 int /*<<< orphan*/  OCSP_R_UNKNOWN_NID ; 
 int /*<<< orphan*/  OCSPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_NULL ; 
 int /*<<< orphan*/  X509_NAME_digest (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned char*,unsigned int*) ; 

OCSP_CERTID *OCSP_cert_id_new(const EVP_MD *dgst,
                              const X509_NAME *issuerName,
                              const ASN1_BIT_STRING *issuerKey,
                              const ASN1_INTEGER *serialNumber)
{
    int nid;
    unsigned int i;
    X509_ALGOR *alg;
    OCSP_CERTID *cid = NULL;
    unsigned char md[EVP_MAX_MD_SIZE];

    if ((cid = OCSP_CERTID_new()) == NULL)
        goto err;

    alg = &cid->hashAlgorithm;
    ASN1_OBJECT_free(alg->algorithm);
    if ((nid = EVP_MD_type(dgst)) == NID_undef) {
        OCSPerr(OCSP_F_OCSP_CERT_ID_NEW, OCSP_R_UNKNOWN_NID);
        goto err;
    }
    if ((alg->algorithm = OBJ_nid2obj(nid)) == NULL)
        goto err;
    if ((alg->parameter = ASN1_TYPE_new()) == NULL)
        goto err;
    alg->parameter->type = V_ASN1_NULL;

    if (!X509_NAME_digest(issuerName, dgst, md, &i))
        goto digerr;
    if (!(ASN1_OCTET_STRING_set(&cid->issuerNameHash, md, i)))
        goto err;

    /* Calculate the issuerKey hash, excluding tag and length */
    if (!EVP_Digest(issuerKey->data, issuerKey->length, md, &i, dgst, NULL))
        goto err;

    if (!(ASN1_OCTET_STRING_set(&cid->issuerKeyHash, md, i)))
        goto err;

    if (serialNumber) {
        if (ASN1_STRING_copy(&cid->serialNumber, serialNumber) == 0)
            goto err;
    }
    return cid;
 digerr:
    OCSPerr(OCSP_F_OCSP_CERT_ID_NEW, OCSP_R_DIGEST_ERR);
 err:
    OCSP_CERTID_free(cid);
    return NULL;
}