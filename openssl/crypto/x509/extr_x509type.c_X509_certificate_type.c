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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
#define  EVP_PKEY_DH 142 
#define  EVP_PKEY_DSA 141 
#define  EVP_PKEY_EC 140 
#define  EVP_PKEY_ED25519 139 
#define  EVP_PKEY_ED448 138 
#define  EVP_PKEY_RSA 137 
#define  EVP_PKEY_RSA_PSS 136 
 int EVP_PKEY_id (int /*<<< orphan*/  const*) ; 
 int EVP_PKS_DSA ; 
 int EVP_PKS_EC ; 
 int EVP_PKS_RSA ; 
 int EVP_PKT_ENC ; 
 int EVP_PKT_EXCH ; 
 int EVP_PKT_SIGN ; 
 int EVP_PK_DH ; 
 int EVP_PK_DSA ; 
 int EVP_PK_EC ; 
 int EVP_PK_RSA ; 
#define  NID_X9_62_id_ecPublicKey 135 
#define  NID_dsa 134 
#define  NID_dsa_2 133 
#define  NID_id_GostR3410_2001 132 
#define  NID_id_GostR3410_2012_256 131 
#define  NID_id_GostR3410_2012_512 130 
#define  NID_rsa 129 
#define  NID_rsaEncryption 128 
 scalar_t__ OBJ_find_sigid_algs (int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/  const*) ; 
 int X509_get_signature_nid (int /*<<< orphan*/  const*) ; 

int X509_certificate_type(const X509 *x, const EVP_PKEY *pkey)
{
    const EVP_PKEY *pk;
    int ret = 0, i;

    if (x == NULL)
        return 0;

    if (pkey == NULL)
        pk = X509_get0_pubkey(x);
    else
        pk = pkey;

    if (pk == NULL)
        return 0;

    switch (EVP_PKEY_id(pk)) {
    case EVP_PKEY_RSA:
        ret = EVP_PK_RSA | EVP_PKT_SIGN;
/*              if (!sign only extension) */
        ret |= EVP_PKT_ENC;
        break;
    case EVP_PKEY_RSA_PSS:
        ret = EVP_PK_RSA | EVP_PKT_SIGN;
        break;
    case EVP_PKEY_DSA:
        ret = EVP_PK_DSA | EVP_PKT_SIGN;
        break;
    case EVP_PKEY_EC:
        ret = EVP_PK_EC | EVP_PKT_SIGN | EVP_PKT_EXCH;
        break;
    case EVP_PKEY_ED448:
    case EVP_PKEY_ED25519:
        ret = EVP_PKT_SIGN;
        break;
    case EVP_PKEY_DH:
        ret = EVP_PK_DH | EVP_PKT_EXCH;
        break;
    case NID_id_GostR3410_2001:
    case NID_id_GostR3410_2012_256:
    case NID_id_GostR3410_2012_512:
        ret = EVP_PKT_EXCH | EVP_PKT_SIGN;
        break;
    default:
        break;
    }

    i = X509_get_signature_nid(x);
    if (i && OBJ_find_sigid_algs(i, NULL, &i)) {

        switch (i) {
        case NID_rsaEncryption:
        case NID_rsa:
            ret |= EVP_PKS_RSA;
            break;
        case NID_dsa:
        case NID_dsa_2:
            ret |= EVP_PKS_DSA;
            break;
        case NID_X9_62_id_ecPublicKey:
            ret |= EVP_PKS_EC;
            break;
        default:
            break;
        }
    }

    return ret;
}