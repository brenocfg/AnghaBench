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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  keybytes ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  OCSP_CERTID ;
typedef  int /*<<< orphan*/  OCSP_BASICRESP ;
typedef  int /*<<< orphan*/  ASN1_TIME ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_BIT_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_BIT_STRING_new () ; 
 int /*<<< orphan*/  ASN1_BIT_STRING_set (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_TIME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_TIME_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int /*<<< orphan*/  MBSTRING_ASC ; 
 int /*<<< orphan*/  NID_commonName ; 
 int /*<<< orphan*/  OCSP_BASICRESP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OCSP_BASICRESP_new () ; 
 int /*<<< orphan*/  OCSP_CERTID_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCSP_basic_add1_status (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OCSP_cert_id_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_OCSP_CERTSTATUS_UNKNOWN ; 
 int /*<<< orphan*/  X509_NAME_add_entry_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,int,int,int) ; 
 int /*<<< orphan*/  X509_NAME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_new () ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OCSP_BASICRESP *make_dummy_resp(void)
{
    const unsigned char namestr[] = "openssl.example.com";
    unsigned char keybytes[128] = {7};
    OCSP_BASICRESP *bs = OCSP_BASICRESP_new();
    OCSP_BASICRESP *bs_out = NULL;
    OCSP_CERTID *cid = NULL;
    ASN1_TIME *thisupd = ASN1_TIME_set(NULL, time(NULL));
    ASN1_TIME *nextupd = ASN1_TIME_set(NULL, time(NULL) + 200);
    X509_NAME *name = X509_NAME_new();
    ASN1_BIT_STRING *key = ASN1_BIT_STRING_new();
    ASN1_INTEGER *serial = ASN1_INTEGER_new();

    if (!X509_NAME_add_entry_by_NID(name, NID_commonName, MBSTRING_ASC,
                                   namestr, -1, -1, 1)
        || !ASN1_BIT_STRING_set(key, keybytes, sizeof(keybytes))
        || !ASN1_INTEGER_set_uint64(serial, (uint64_t)1))
        goto err;
    cid = OCSP_cert_id_new(EVP_sha256(), name, key, serial);
    if (!TEST_ptr(bs)
        || !TEST_ptr(thisupd)
        || !TEST_ptr(nextupd)
        || !TEST_ptr(cid)
        || !TEST_true(OCSP_basic_add1_status(bs, cid,
                                             V_OCSP_CERTSTATUS_UNKNOWN,
                                             0, NULL, thisupd, nextupd)))
        goto err;
    bs_out = bs;
    bs = NULL;
 err:
    ASN1_TIME_free(thisupd);
    ASN1_TIME_free(nextupd);
    ASN1_BIT_STRING_free(key);
    ASN1_INTEGER_free(serial);
    OCSP_CERTID_free(cid);
    OCSP_BASICRESP_free(bs);
    X509_NAME_free(name);
    return bs_out;
}