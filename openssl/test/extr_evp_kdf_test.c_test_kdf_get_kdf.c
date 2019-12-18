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
typedef  int /*<<< orphan*/  EVP_KDF ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_KDF_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LN_tls1_prf ; 
 int /*<<< orphan*/  NID_id_pbkdf2 ; 
 int /*<<< orphan*/  NID_tls1_prf ; 
 int /*<<< orphan*/ * OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_nid2sn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_obj2nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_KDF_NAME_PBKDF2 ; 
 int /*<<< orphan*/  SN_tls1_prf ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_kdf_get_kdf(void)
{
    EVP_KDF *kdf1 = NULL, *kdf2 = NULL;
    ASN1_OBJECT *obj;
    int ok = 1;

    if (!TEST_ptr(obj = OBJ_nid2obj(NID_id_pbkdf2))
        || !TEST_ptr(kdf1 = EVP_KDF_fetch(NULL, OSSL_KDF_NAME_PBKDF2, NULL))
        || !TEST_ptr(kdf2 = EVP_KDF_fetch(NULL, OBJ_nid2sn(OBJ_obj2nid(obj)),
                                          NULL))
        || !TEST_ptr_eq(kdf1, kdf2))
        ok = 0;
    EVP_KDF_free(kdf1);
    kdf1 = NULL;
    EVP_KDF_free(kdf2);
    kdf2 = NULL;

    if (!TEST_ptr(kdf1 = EVP_KDF_fetch(NULL, SN_tls1_prf, NULL))
        || !TEST_ptr(kdf2 = EVP_KDF_fetch(NULL, LN_tls1_prf, NULL))
        || !TEST_ptr_eq(kdf1, kdf2))
        ok = 0;
    /* kdf1 is re-used below, so don't free it here */
    EVP_KDF_free(kdf2);
    kdf2 = NULL;

    if (!TEST_ptr(kdf2 = EVP_KDF_fetch(NULL, OBJ_nid2sn(NID_tls1_prf), NULL))
        || !TEST_ptr_eq(kdf1, kdf2))
        ok = 0;
    EVP_KDF_free(kdf1);
    kdf1 = NULL;
    EVP_KDF_free(kdf2);
    kdf2 = NULL;

    return ok;
}