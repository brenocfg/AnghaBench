#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mac; int /*<<< orphan*/  iterationCount; int /*<<< orphan*/  owf; int /*<<< orphan*/  salt; } ;
typedef  TYPE_1__ OSSL_CRMF_PBMPARAMETER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  CRMF_F_OSSL_CRMF_PBMP_NEW ; 
 int /*<<< orphan*/  CRMF_R_CRMFERROR ; 
 int /*<<< orphan*/  CRMF_R_FAILURE_OBTAINING_RANDOM ; 
 int /*<<< orphan*/  CRMF_R_ITERATIONCOUNT_BELOW_100 ; 
 int /*<<< orphan*/  CRMF_R_SETTING_MAC_ALGOR_FAILURE ; 
 int /*<<< orphan*/  CRMF_R_SETTING_OWF_ALGOR_FAILURE ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_nid2obj (int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  OSSL_CRMF_PBMPARAMETER_free (TYPE_1__*) ; 
 TYPE_1__* OSSL_CRMF_PBMPARAMETER_new () ; 
 scalar_t__ RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  V_ASN1_UNDEF ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

OSSL_CRMF_PBMPARAMETER *OSSL_CRMF_pbmp_new(size_t slen, int owfnid,
                                           int itercnt, int macnid)
{
    OSSL_CRMF_PBMPARAMETER *pbm = NULL;
    unsigned char *salt = NULL;

    if ((pbm = OSSL_CRMF_PBMPARAMETER_new()) == NULL)
        goto err;

    /*
     * salt contains a randomly generated value used in computing the key
     * of the MAC process.  The salt SHOULD be at least 8 octets (64
     * bits) long.
     */
    if ((salt = OPENSSL_malloc(slen)) == NULL)
        goto err;
    if (RAND_bytes(salt, (int)slen) <= 0) {
        CRMFerr(CRMF_F_OSSL_CRMF_PBMP_NEW, CRMF_R_FAILURE_OBTAINING_RANDOM);
        goto err;
    }
    if (!ASN1_OCTET_STRING_set(pbm->salt, salt, (int)slen))
        goto err;

    /*
     * owf identifies the hash algorithm and associated parameters used to
     * compute the key used in the MAC process.  All implementations MUST
     * support SHA-1.
     */
    if (!X509_ALGOR_set0(pbm->owf, OBJ_nid2obj(owfnid), V_ASN1_UNDEF, NULL)) {
        CRMFerr(CRMF_F_OSSL_CRMF_PBMP_NEW, CRMF_R_SETTING_OWF_ALGOR_FAILURE);
        goto err;
    }

    /*
     * iterationCount identifies the number of times the hash is applied
     * during the key computation process.  The iterationCount MUST be a
     * minimum of 100.      Many people suggest using values as high as 1000
     * iterations as the minimum value.  The trade off here is between
     * protection of the password from attacks and the time spent by the
     * server processing all of the different iterations in deriving
     * passwords.  Hashing is generally considered a cheap operation but
     * this may not be true with all hash functions in the future.
     */
    if (itercnt < 100) {
        CRMFerr(CRMF_F_OSSL_CRMF_PBMP_NEW, CRMF_R_ITERATIONCOUNT_BELOW_100);
        goto err;
    }

    if (!ASN1_INTEGER_set(pbm->iterationCount, itercnt)) {
        CRMFerr(CRMF_F_OSSL_CRMF_PBMP_NEW, CRMF_R_CRMFERROR);
        goto err;
    }

    /*
     * mac identifies the algorithm and associated parameters of the MAC
     * function to be used.  All implementations MUST support HMAC-SHA1 [HMAC].
     * All implementations SHOULD support DES-MAC and Triple-DES-MAC [PKCS11].
     */
    if (!X509_ALGOR_set0(pbm->mac, OBJ_nid2obj(macnid), V_ASN1_UNDEF, NULL)) {
        CRMFerr(CRMF_F_OSSL_CRMF_PBMP_NEW, CRMF_R_SETTING_MAC_ALGOR_FAILURE);
        goto err;
    }

    OPENSSL_free(salt);
    return pbm;
 err:
    OPENSSL_free(salt);
    OSSL_CRMF_PBMPARAMETER_free(pbm);
    return NULL;
}