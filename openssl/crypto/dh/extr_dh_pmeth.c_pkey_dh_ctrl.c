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
struct TYPE_5__ {int prime_len; int use_dsa; int subprime_len; int pad; int generator; int param_nid; int rfc5114_param; int kdf_type; size_t kdf_outlen; unsigned char* kdf_ukm; int kdf_ukmlen; int /*<<< orphan*/ * kdf_oid; int /*<<< orphan*/ * kdf_md; } ;
struct TYPE_4__ {TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_2__ DH_PKEY_CTX ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
#define  EVP_PKEY_CTRL_DH_KDF_MD 144 
#define  EVP_PKEY_CTRL_DH_KDF_OID 143 
#define  EVP_PKEY_CTRL_DH_KDF_OUTLEN 142 
#define  EVP_PKEY_CTRL_DH_KDF_TYPE 141 
#define  EVP_PKEY_CTRL_DH_KDF_UKM 140 
#define  EVP_PKEY_CTRL_DH_NID 139 
#define  EVP_PKEY_CTRL_DH_PAD 138 
#define  EVP_PKEY_CTRL_DH_PARAMGEN_GENERATOR 137 
#define  EVP_PKEY_CTRL_DH_PARAMGEN_PRIME_LEN 136 
#define  EVP_PKEY_CTRL_DH_PARAMGEN_SUBPRIME_LEN 135 
#define  EVP_PKEY_CTRL_DH_PARAMGEN_TYPE 134 
#define  EVP_PKEY_CTRL_DH_RFC5114 133 
#define  EVP_PKEY_CTRL_GET_DH_KDF_MD 132 
#define  EVP_PKEY_CTRL_GET_DH_KDF_OID 131 
#define  EVP_PKEY_CTRL_GET_DH_KDF_OUTLEN 130 
#define  EVP_PKEY_CTRL_GET_DH_KDF_UKM 129 
#define  EVP_PKEY_CTRL_PEER_KEY 128 
 int EVP_PKEY_DH_KDF_NONE ; 
 int EVP_PKEY_DH_KDF_X9_42 ; 
 int NID_undef ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 

__attribute__((used)) static int pkey_dh_ctrl(EVP_PKEY_CTX *ctx, int type, int p1, void *p2)
{
    DH_PKEY_CTX *dctx = ctx->data;
    switch (type) {
    case EVP_PKEY_CTRL_DH_PARAMGEN_PRIME_LEN:
        if (p1 < 256)
            return -2;
        dctx->prime_len = p1;
        return 1;

    case EVP_PKEY_CTRL_DH_PARAMGEN_SUBPRIME_LEN:
        if (dctx->use_dsa == 0)
            return -2;
        dctx->subprime_len = p1;
        return 1;

    case EVP_PKEY_CTRL_DH_PAD:
        dctx->pad = p1;
        return 1;

    case EVP_PKEY_CTRL_DH_PARAMGEN_GENERATOR:
        if (dctx->use_dsa)
            return -2;
        dctx->generator = p1;
        return 1;

    case EVP_PKEY_CTRL_DH_PARAMGEN_TYPE:
#ifdef OPENSSL_NO_DSA
        if (p1 != 0)
            return -2;
#else
        if (p1 < 0 || p1 > 2)
            return -2;
#endif
        dctx->use_dsa = p1;
        return 1;

    case EVP_PKEY_CTRL_DH_RFC5114:
        if (p1 < 1 || p1 > 3 || dctx->param_nid != NID_undef)
            return -2;
        dctx->rfc5114_param = p1;
        return 1;

    case EVP_PKEY_CTRL_DH_NID:
        if (p1 <= 0 || dctx->rfc5114_param != 0)
            return -2;
        dctx->param_nid = p1;
        return 1;

    case EVP_PKEY_CTRL_PEER_KEY:
        /* Default behaviour is OK */
        return 1;

    case EVP_PKEY_CTRL_DH_KDF_TYPE:
        if (p1 == -2)
            return dctx->kdf_type;
#ifdef OPENSSL_NO_CMS
        if (p1 != EVP_PKEY_DH_KDF_NONE)
#else
        if (p1 != EVP_PKEY_DH_KDF_NONE && p1 != EVP_PKEY_DH_KDF_X9_42)
#endif
            return -2;
        dctx->kdf_type = p1;
        return 1;

    case EVP_PKEY_CTRL_DH_KDF_MD:
        dctx->kdf_md = p2;
        return 1;

    case EVP_PKEY_CTRL_GET_DH_KDF_MD:
        *(const EVP_MD **)p2 = dctx->kdf_md;
        return 1;

    case EVP_PKEY_CTRL_DH_KDF_OUTLEN:
        if (p1 <= 0)
            return -2;
        dctx->kdf_outlen = (size_t)p1;
        return 1;

    case EVP_PKEY_CTRL_GET_DH_KDF_OUTLEN:
        *(int *)p2 = dctx->kdf_outlen;
        return 1;

    case EVP_PKEY_CTRL_DH_KDF_UKM:
        OPENSSL_free(dctx->kdf_ukm);
        dctx->kdf_ukm = p2;
        if (p2)
            dctx->kdf_ukmlen = p1;
        else
            dctx->kdf_ukmlen = 0;
        return 1;

    case EVP_PKEY_CTRL_GET_DH_KDF_UKM:
        *(unsigned char **)p2 = dctx->kdf_ukm;
        return dctx->kdf_ukmlen;

    case EVP_PKEY_CTRL_DH_KDF_OID:
        ASN1_OBJECT_free(dctx->kdf_oid);
        dctx->kdf_oid = p2;
        return 1;

    case EVP_PKEY_CTRL_GET_DH_KDF_OID:
        *(ASN1_OBJECT **)p2 = dctx->kdf_oid;
        return 1;

    default:
        return -2;

    }
}