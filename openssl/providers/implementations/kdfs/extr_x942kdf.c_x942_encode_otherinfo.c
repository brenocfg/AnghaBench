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
typedef  int /*<<< orphan*/  ctr ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int CMS_SharedInfo_encode (unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ CRYPTO_memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/ * OBJ_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_nid2obj (int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  V_ASN1_OBJECT ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/  X509_ALGOR_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_ALGOR_new () ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skip_asn1 (unsigned char**,long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x942_encode_otherinfo(int nid, size_t keylen,
                                 const unsigned char *ukm, size_t ukmlen,
                                 unsigned char **der, size_t *der_len,
                                 unsigned char **out_ctr)
{
    unsigned char *p, *encoded = NULL;
    int ret = 0, encoded_len;
    long tlen;
    /* "magic" value to check offset is sane */
    static unsigned char ctr[4] = { 0x00, 0x00, 0x00, 0x01 };
    X509_ALGOR *ksi = NULL;
    ASN1_OBJECT *alg_oid = NULL;
    ASN1_OCTET_STRING *ctr_oct = NULL, *ukm_oct = NULL;

    /* set the KeySpecificInfo - which contains an algorithm oid and counter */
    ksi = X509_ALGOR_new();
    alg_oid = OBJ_dup(OBJ_nid2obj(nid));
    ctr_oct = ASN1_OCTET_STRING_new();
    if (ksi == NULL
        || alg_oid == NULL
        || ctr_oct == NULL
        || !ASN1_OCTET_STRING_set(ctr_oct, ctr, sizeof(ctr))
        || !X509_ALGOR_set0(ksi, alg_oid, V_ASN1_OCTET_STRING, ctr_oct))
        goto err;
    /* NULL these as they now belong to ksi */
    alg_oid = NULL;
    ctr_oct = NULL;

    /* Set the optional partyAInfo */
    if (ukm != NULL) {
        ukm_oct = ASN1_OCTET_STRING_new();
        if (ukm_oct == NULL)
            goto err;
        ASN1_OCTET_STRING_set(ukm_oct, (unsigned char *)ukm, ukmlen);
    }
    /* Generate the OtherInfo DER data */
    encoded_len = CMS_SharedInfo_encode(&encoded, ksi, ukm_oct, keylen);
    if (encoded_len <= 0)
        goto err;

    /* Parse the encoded data to find the offset of the counter data */
    p = encoded;
    tlen = (long)encoded_len;
    if (skip_asn1(&p, &tlen, V_ASN1_SEQUENCE)
        && skip_asn1(&p, &tlen, V_ASN1_SEQUENCE)
        && skip_asn1(&p, &tlen, V_ASN1_OBJECT)
        && skip_asn1(&p, &tlen, V_ASN1_OCTET_STRING)
        && CRYPTO_memcmp(p, ctr, 4) == 0) {
        *out_ctr = p;
        *der = encoded;
        *der_len = (size_t)encoded_len;
        ret = 1;
    }
err:
    if (ret != 1)
        OPENSSL_free(encoded);
    ASN1_OCTET_STRING_free(ctr_oct);
    ASN1_OCTET_STRING_free(ukm_oct);
    ASN1_OBJECT_free(alg_oid);
    X509_ALGOR_free(ksi);
    return ret;
}