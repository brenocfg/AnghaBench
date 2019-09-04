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
typedef  int /*<<< orphan*/  const ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_get_kdfbyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_get_kdfbynid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_get_kdfbyobj (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LN_id_pbkdf2 ; 
 int /*<<< orphan*/  LN_tls1_prf ; 
 int /*<<< orphan*/  NID_id_pbkdf2 ; 
 int /*<<< orphan*/  NID_tls1_prf ; 
 int /*<<< orphan*/ * OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SN_tls1_prf ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/  const*) ; 
 scalar_t__ TEST_ptr_eq (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int test_kdf_get_kdf(void)
{
    const EVP_KDF *kdf1, *kdf2;
    ASN1_OBJECT *obj;

    return
        TEST_ptr(obj = OBJ_nid2obj(NID_id_pbkdf2))
        && TEST_ptr(kdf1 = EVP_get_kdfbyname(LN_id_pbkdf2))
        && TEST_ptr(kdf2 = EVP_get_kdfbyobj(obj))
        && TEST_ptr_eq(kdf1, kdf2)
        && TEST_ptr(kdf1 = EVP_get_kdfbyname(SN_tls1_prf))
        && TEST_ptr(kdf2 = EVP_get_kdfbyname(LN_tls1_prf))
        && TEST_ptr_eq(kdf1, kdf2)
        && TEST_ptr(kdf2 = EVP_get_kdfbynid(NID_tls1_prf))
        && TEST_ptr_eq(kdf1, kdf2);
}