#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  finsecret ;
struct TYPE_12__ {unsigned char* server_finished_secret; unsigned char* client_finished_secret; int /*<<< orphan*/  client_app_traffic_secret; TYPE_2__* method; } ;
struct TYPE_11__ {TYPE_1__* ssl3_enc; } ;
struct TYPE_10__ {char const* server_finished_label; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ EVP_DigestSignFinal (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 scalar_t__ EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestSignUpdate (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_PKEY_HMAC ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new_raw_private_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS13_FINAL_FINISH_MAC ; 
 scalar_t__ SSL_IS_FIRST_HANDSHAKE (TYPE_3__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_handshake_hash (TYPE_3__*,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/ * ssl_handshake_md (TYPE_3__*) ; 
 int /*<<< orphan*/  tls13_derive_finishedkey (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t) ; 

size_t tls13_final_finish_mac(SSL *s, const char *str, size_t slen,
                             unsigned char *out)
{
    const EVP_MD *md = ssl_handshake_md(s);
    unsigned char hash[EVP_MAX_MD_SIZE];
    size_t hashlen, ret = 0;
    EVP_PKEY *key = NULL;
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();

    if (!ssl_handshake_hash(s, hash, sizeof(hash), &hashlen)) {
        /* SSLfatal() already called */
        goto err;
    }

    if (str == s->method->ssl3_enc->server_finished_label) {
        key = EVP_PKEY_new_raw_private_key(EVP_PKEY_HMAC, NULL,
                                           s->server_finished_secret, hashlen);
    } else if (SSL_IS_FIRST_HANDSHAKE(s)) {
        key = EVP_PKEY_new_raw_private_key(EVP_PKEY_HMAC, NULL,
                                           s->client_finished_secret, hashlen);
    } else {
        unsigned char finsecret[EVP_MAX_MD_SIZE];

        if (!tls13_derive_finishedkey(s, ssl_handshake_md(s),
                                      s->client_app_traffic_secret,
                                      finsecret, hashlen))
            goto err;

        key = EVP_PKEY_new_raw_private_key(EVP_PKEY_HMAC, NULL, finsecret,
                                           hashlen);
        OPENSSL_cleanse(finsecret, sizeof(finsecret));
    }

    if (key == NULL
            || ctx == NULL
            || EVP_DigestSignInit(ctx, NULL, md, NULL, key) <= 0
            || EVP_DigestSignUpdate(ctx, hash, hashlen) <= 0
            || EVP_DigestSignFinal(ctx, out, &hashlen) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_FINAL_FINISH_MAC,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    ret = hashlen;
 err:
    EVP_PKEY_free(key);
    EVP_MD_CTX_free(ctx);
    return ret;
}