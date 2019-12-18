#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_PUBKEY ;
struct TYPE_4__ {int /*<<< orphan*/ * ec; } ;
struct TYPE_5__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (void*) ; 
 int /*<<< orphan*/  ASN1_STRING_free (void*) ; 
 int /*<<< orphan*/  EC_F_ECKEY_PUB_ENCODE ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  EVP_PKEY_EC ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int V_ASN1_OBJECT ; 
 scalar_t__ X509_PUBKEY_set0_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void*,unsigned char*,int) ; 
 int /*<<< orphan*/  eckey_param2type (int*,void**,int /*<<< orphan*/ *) ; 
 int i2o_ECPublicKey (int /*<<< orphan*/ *,unsigned char**) ; 

__attribute__((used)) static int eckey_pub_encode(X509_PUBKEY *pk, const EVP_PKEY *pkey)
{
    EC_KEY *ec_key = pkey->pkey.ec;
    void *pval = NULL;
    int ptype;
    unsigned char *penc = NULL, *p;
    int penclen;

    if (!eckey_param2type(&ptype, &pval, ec_key)) {
        ECerr(EC_F_ECKEY_PUB_ENCODE, ERR_R_EC_LIB);
        return 0;
    }
    penclen = i2o_ECPublicKey(ec_key, NULL);
    if (penclen <= 0)
        goto err;
    penc = OPENSSL_malloc(penclen);
    if (penc == NULL)
        goto err;
    p = penc;
    penclen = i2o_ECPublicKey(ec_key, &p);
    if (penclen <= 0)
        goto err;
    if (X509_PUBKEY_set0_param(pk, OBJ_nid2obj(EVP_PKEY_EC),
                               ptype, pval, penc, penclen))
        return 1;
 err:
    if (ptype == V_ASN1_OBJECT)
        ASN1_OBJECT_free(pval);
    else
        ASN1_STRING_free(pval);
    OPENSSL_free(penc);
    return 0;
}