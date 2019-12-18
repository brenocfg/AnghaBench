#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_PUBKEY ;
struct TYPE_10__ {int /*<<< orphan*/  pubkey; } ;
struct TYPE_7__ {TYPE_4__* ecx; } ;
struct TYPE_9__ {TYPE_2__* ameth; TYPE_1__ pkey; } ;
struct TYPE_8__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_3__ EVP_PKEY ;
typedef  TYPE_4__ ECX_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_ECX_PUB_ENCODE ; 
 int /*<<< orphan*/  EC_R_INVALID_KEY ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  KEYLEN (TYPE_3__ const*) ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_memdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_UNDEF ; 
 int /*<<< orphan*/  X509_PUBKEY_set0_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecx_pub_encode(X509_PUBKEY *pk, const EVP_PKEY *pkey)
{
    const ECX_KEY *ecxkey = pkey->pkey.ecx;
    unsigned char *penc;

    if (ecxkey == NULL) {
        ECerr(EC_F_ECX_PUB_ENCODE, EC_R_INVALID_KEY);
        return 0;
    }

    penc = OPENSSL_memdup(ecxkey->pubkey, KEYLEN(pkey));
    if (penc == NULL) {
        ECerr(EC_F_ECX_PUB_ENCODE, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    if (!X509_PUBKEY_set0_param(pk, OBJ_nid2obj(pkey->ameth->pkey_id),
                                V_ASN1_UNDEF, NULL, penc, KEYLEN(pkey))) {
        OPENSSL_free(penc);
        ECerr(EC_F_ECX_PUB_ENCODE, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    return 1;
}