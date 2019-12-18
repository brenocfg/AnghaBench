#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  nid; } ;
typedef  TYPE_1__ TLS_GROUP_INFO ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  DH ;

/* Variables and functions */
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DH_new_by_nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set_dh_nid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_CTX_set_ec_paramgen_curve_nid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_DH ; 
 int /*<<< orphan*/  EVP_PKEY_EC ; 
 int /*<<< orphan*/  EVP_PKEY_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_keygen (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ EVP_PKEY_keygen_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL_GENERATE_PKEY_GROUP ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLS_GROUP_CURVE_CUSTOM ; 
 int TLS_GROUP_FFDHE ; 
 int TLS_GROUP_TYPE ; 
 TYPE_1__* tls1_group_id_lookup (int) ; 

EVP_PKEY *ssl_generate_pkey_group(SSL *s, uint16_t id)
{
    const TLS_GROUP_INFO *ginf = tls1_group_id_lookup(id);
    EVP_PKEY_CTX *pctx = NULL;
    EVP_PKEY *pkey = NULL;
    uint16_t gtype;
# ifndef OPENSSL_NO_DH
    DH *dh = NULL;
# endif

    if (ginf == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }
    gtype = ginf->flags & TLS_GROUP_TYPE;
# ifndef OPENSSL_NO_DH
    if (gtype == TLS_GROUP_FFDHE)
        pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_DH, NULL);
#  ifndef OPENSSL_NO_EC
    else
#  endif
# endif
# ifndef OPENSSL_NO_EC
    {
        if (gtype == TLS_GROUP_CURVE_CUSTOM)
            pctx = EVP_PKEY_CTX_new_id(ginf->nid, NULL);
        else
            pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL);
    }
# endif
    if (pctx == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }
    if (EVP_PKEY_keygen_init(pctx) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                 ERR_R_EVP_LIB);
        goto err;
    }
# ifndef OPENSSL_NO_DH
    if (gtype == TLS_GROUP_FFDHE) {
        if ((pkey = EVP_PKEY_new()) == NULL
                || (dh = DH_new_by_nid(ginf->nid)) == NULL
                || !EVP_PKEY_assign(pkey, EVP_PKEY_DH, dh)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                    ERR_R_EVP_LIB);
            DH_free(dh);
            EVP_PKEY_free(pkey);
            pkey = NULL;
            goto err;
        }
        if (EVP_PKEY_CTX_set_dh_nid(pctx, ginf->nid) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                    ERR_R_EVP_LIB);
            EVP_PKEY_free(pkey);
            pkey = NULL;
            goto err;
        }
    }
#  ifndef OPENSSL_NO_EC
    else
#  endif
# endif
# ifndef OPENSSL_NO_EC
    {
        if (gtype != TLS_GROUP_CURVE_CUSTOM
                && EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pctx, ginf->nid) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                     ERR_R_EVP_LIB);
            goto err;
        }
    }
# endif
    if (EVP_PKEY_keygen(pctx, &pkey) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                 ERR_R_EVP_LIB);
        EVP_PKEY_free(pkey);
        pkey = NULL;
    }

 err:
    EVP_PKEY_CTX_free(pctx);
    return pkey;
}