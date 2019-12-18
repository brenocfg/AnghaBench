#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  handshake_dgst; } ;
struct TYPE_7__ {int /*<<< orphan*/  session; TYPE_1__ s3; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestUpdate (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  EVP_MD_CTX_copy_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 scalar_t__ EVP_MD_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_MD_CTX_size (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_MD_CTX_type (int /*<<< orphan*/ ) ; 
 scalar_t__ NID_md5_sha1 ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL3_FINAL_FINISH_MAC ; 
 int /*<<< orphan*/  SSL_R_NO_REQUIRED_DIGEST ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl3_digest_cached_records (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl3_digest_master_key_set_params (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

size_t ssl3_final_finish_mac(SSL *s, const char *sender, size_t len,
                             unsigned char *p)
{
    int ret;
    EVP_MD_CTX *ctx = NULL;

    if (!ssl3_digest_cached_records(s, 0)) {
        /* SSLfatal() already called */
        return 0;
    }

    if (EVP_MD_CTX_type(s->s3.handshake_dgst) != NID_md5_sha1) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_FINAL_FINISH_MAC,
                 SSL_R_NO_REQUIRED_DIGEST);
        return 0;
    }

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_FINAL_FINISH_MAC,
                 ERR_R_MALLOC_FAILURE);
        return 0;
    }
    if (!EVP_MD_CTX_copy_ex(ctx, s->s3.handshake_dgst)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_FINAL_FINISH_MAC,
                 ERR_R_INTERNAL_ERROR);
        ret = 0;
        goto err;
    }

    ret = EVP_MD_CTX_size(ctx);
    if (ret < 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_FINAL_FINISH_MAC,
                 ERR_R_INTERNAL_ERROR);
        ret = 0;
        goto err;
    }

    if (sender != NULL) {
        OSSL_PARAM digest_cmd_params[3];

        ssl3_digest_master_key_set_params(s->session, digest_cmd_params);

        if (EVP_DigestUpdate(ctx, sender, len) <= 0
            || EVP_MD_CTX_set_params(ctx, digest_cmd_params) <= 0
            || EVP_DigestFinal_ex(ctx, p, NULL) <= 0) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_FINAL_FINISH_MAC,
                         ERR_R_INTERNAL_ERROR);
                ret = 0;
        }
    }

 err:
    EVP_MD_CTX_free(ctx);

    return ret;
}