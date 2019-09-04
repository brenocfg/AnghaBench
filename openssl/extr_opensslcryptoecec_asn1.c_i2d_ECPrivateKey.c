#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int flags; } ;
struct TYPE_12__ {int enc_flag; int /*<<< orphan*/  conv_form; int /*<<< orphan*/ * group; int /*<<< orphan*/  version; int /*<<< orphan*/ * pub_key; } ;
struct TYPE_11__ {TYPE_9__* publicKey; int /*<<< orphan*/ * parameters; TYPE_9__* privateKey; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ EC_PRIVATEKEY ;
typedef  TYPE_2__ EC_KEY ;

/* Variables and functions */
 TYPE_9__* ASN1_BIT_STRING_new () ; 
 int ASN1_STRING_FLAG_BITS_LEFT ; 
 int /*<<< orphan*/  ASN1_STRING_set0 (TYPE_9__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EC_F_I2D_ECPRIVATEKEY ; 
 int /*<<< orphan*/ * EC_GROUP_get_ecpkparameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t EC_KEY_key2buf (TYPE_2__ const*,int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *) ; 
 size_t EC_KEY_priv2buf (TYPE_2__ const*,unsigned char**) ; 
 int EC_PKEY_NO_PARAMETERS ; 
 int EC_PKEY_NO_PUBKEY ; 
 int /*<<< orphan*/  EC_PRIVATEKEY_free (TYPE_1__*) ; 
 TYPE_1__* EC_PRIVATEKEY_new () ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int i2d_EC_PRIVATEKEY (TYPE_1__*,unsigned char**) ; 

int i2d_ECPrivateKey(const EC_KEY *a, unsigned char **out)
{
    int ret = 0, ok = 0;
    unsigned char *priv= NULL, *pub= NULL;
    size_t privlen = 0, publen = 0;

    EC_PRIVATEKEY *priv_key = NULL;

    if (a == NULL || a->group == NULL ||
        (!(a->enc_flag & EC_PKEY_NO_PUBKEY) && a->pub_key == NULL)) {
        ECerr(EC_F_I2D_ECPRIVATEKEY, ERR_R_PASSED_NULL_PARAMETER);
        goto err;
    }

    if ((priv_key = EC_PRIVATEKEY_new()) == NULL) {
        ECerr(EC_F_I2D_ECPRIVATEKEY, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    priv_key->version = a->version;

    privlen = EC_KEY_priv2buf(a, &priv);

    if (privlen == 0) {
        ECerr(EC_F_I2D_ECPRIVATEKEY, ERR_R_EC_LIB);
        goto err;
    }

    ASN1_STRING_set0(priv_key->privateKey, priv, privlen);
    priv = NULL;

    if (!(a->enc_flag & EC_PKEY_NO_PARAMETERS)) {
        if ((priv_key->parameters =
             EC_GROUP_get_ecpkparameters(a->group,
                                        priv_key->parameters)) == NULL) {
            ECerr(EC_F_I2D_ECPRIVATEKEY, ERR_R_EC_LIB);
            goto err;
        }
    }

    if (!(a->enc_flag & EC_PKEY_NO_PUBKEY)) {
        priv_key->publicKey = ASN1_BIT_STRING_new();
        if (priv_key->publicKey == NULL) {
            ECerr(EC_F_I2D_ECPRIVATEKEY, ERR_R_MALLOC_FAILURE);
            goto err;
        }

        publen = EC_KEY_key2buf(a, a->conv_form, &pub, NULL);

        if (publen == 0) {
            ECerr(EC_F_I2D_ECPRIVATEKEY, ERR_R_EC_LIB);
            goto err;
        }

        priv_key->publicKey->flags &= ~(ASN1_STRING_FLAG_BITS_LEFT | 0x07);
        priv_key->publicKey->flags |= ASN1_STRING_FLAG_BITS_LEFT;
        ASN1_STRING_set0(priv_key->publicKey, pub, publen);
        pub = NULL;
    }

    if ((ret = i2d_EC_PRIVATEKEY(priv_key, out)) == 0) {
        ECerr(EC_F_I2D_ECPRIVATEKEY, ERR_R_EC_LIB);
        goto err;
    }
    ok = 1;
 err:
    OPENSSL_clear_free(priv, privlen);
    OPENSSL_free(pub);
    EC_PRIVATEKEY_free(priv_key);
    return (ok ? ret : 0);
}