#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ algorithm_enc; scalar_t__ algorithm_mac; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int ssl_version; int /*<<< orphan*/  compress_meth; TYPE_3__* cipher; } ;
typedef  TYPE_1__ SSL_SESSION ;
typedef  TYPE_2__ SSL_COMP ;
typedef  TYPE_3__ SSL_CIPHER ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int EVP_CIPHER_flags (int /*<<< orphan*/  const*) ; 
 int EVP_CIPH_FLAG_AEAD_CIPHER ; 
 int /*<<< orphan*/ * EVP_enc_null () ; 
 int /*<<< orphan*/ * EVP_get_cipherbyname (char*) ; 
 int NID_undef ; 
 scalar_t__ SSL_AEAD ; 
 scalar_t__ SSL_AES128 ; 
 scalar_t__ SSL_AES256 ; 
 int SSL_ENC_NULL_IDX ; 
 scalar_t__ SSL_MD5 ; 
 scalar_t__ SSL_RC4 ; 
 scalar_t__ SSL_SHA1 ; 
 scalar_t__ SSL_SHA256 ; 
 int TLS1_VERSION ; 
 int TLS1_VERSION_MAJOR ; 
 int /*<<< orphan*/  load_builtin_compressions () ; 
 int sk_SSL_COMP_find (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* sk_SSL_COMP_value (int /*<<< orphan*/ *,int) ; 
 int ssl_cipher_info_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ ** ssl_cipher_methods ; 
 int /*<<< orphan*/  ssl_cipher_table_cipher ; 
 int /*<<< orphan*/  ssl_cipher_table_mac ; 
 int /*<<< orphan*/ * ssl_comp_methods ; 
 int /*<<< orphan*/ ** ssl_digest_methods ; 
 int* ssl_mac_pkey_id ; 
 size_t* ssl_mac_secret_size ; 

int ssl_cipher_get_evp(const SSL_SESSION *s, const EVP_CIPHER **enc,
                       const EVP_MD **md, int *mac_pkey_type,
                       size_t *mac_secret_size, SSL_COMP **comp, int use_etm)
{
    int i;
    const SSL_CIPHER *c;

    c = s->cipher;
    if (c == NULL)
        return 0;
    if (comp != NULL) {
        SSL_COMP ctmp;
#ifndef OPENSSL_NO_COMP
        if (!load_builtin_compressions()) {
            /*
             * Currently don't care, since a failure only means that
             * ssl_comp_methods is NULL, which is perfectly OK
             */
        }
#endif
        *comp = NULL;
        ctmp.id = s->compress_meth;
        if (ssl_comp_methods != NULL) {
            i = sk_SSL_COMP_find(ssl_comp_methods, &ctmp);
            *comp = sk_SSL_COMP_value(ssl_comp_methods, i);
        }
        /* If were only interested in comp then return success */
        if ((enc == NULL) && (md == NULL))
            return 1;
    }

    if ((enc == NULL) || (md == NULL))
        return 0;

    i = ssl_cipher_info_lookup(ssl_cipher_table_cipher, c->algorithm_enc);

    if (i == -1) {
        *enc = NULL;
    } else {
        if (i == SSL_ENC_NULL_IDX)
            *enc = EVP_enc_null();
        else
            *enc = ssl_cipher_methods[i];
    }

    i = ssl_cipher_info_lookup(ssl_cipher_table_mac, c->algorithm_mac);
    if (i == -1) {
        *md = NULL;
        if (mac_pkey_type != NULL)
            *mac_pkey_type = NID_undef;
        if (mac_secret_size != NULL)
            *mac_secret_size = 0;
        if (c->algorithm_mac == SSL_AEAD)
            mac_pkey_type = NULL;
    } else {
        *md = ssl_digest_methods[i];
        if (mac_pkey_type != NULL)
            *mac_pkey_type = ssl_mac_pkey_id[i];
        if (mac_secret_size != NULL)
            *mac_secret_size = ssl_mac_secret_size[i];
    }

    if ((*enc != NULL) &&
        (*md != NULL || (EVP_CIPHER_flags(*enc) & EVP_CIPH_FLAG_AEAD_CIPHER))
        && (!mac_pkey_type || *mac_pkey_type != NID_undef)) {
        const EVP_CIPHER *evp;

        if (use_etm)
            return 1;

        if (s->ssl_version >> 8 != TLS1_VERSION_MAJOR ||
            s->ssl_version < TLS1_VERSION)
            return 1;

        if (c->algorithm_enc == SSL_RC4 &&
            c->algorithm_mac == SSL_MD5 &&
            (evp = EVP_get_cipherbyname("RC4-HMAC-MD5")))
            *enc = evp, *md = NULL;
        else if (c->algorithm_enc == SSL_AES128 &&
                 c->algorithm_mac == SSL_SHA1 &&
                 (evp = EVP_get_cipherbyname("AES-128-CBC-HMAC-SHA1")))
            *enc = evp, *md = NULL;
        else if (c->algorithm_enc == SSL_AES256 &&
                 c->algorithm_mac == SSL_SHA1 &&
                 (evp = EVP_get_cipherbyname("AES-256-CBC-HMAC-SHA1")))
            *enc = evp, *md = NULL;
        else if (c->algorithm_enc == SSL_AES128 &&
                 c->algorithm_mac == SSL_SHA256 &&
                 (evp = EVP_get_cipherbyname("AES-128-CBC-HMAC-SHA256")))
            *enc = evp, *md = NULL;
        else if (c->algorithm_enc == SSL_AES256 &&
                 c->algorithm_mac == SSL_SHA256 &&
                 (evp = EVP_get_cipherbyname("AES-256-CBC-HMAC-SHA256")))
            *enc = evp, *md = NULL;
        return 1;
    } else {
        return 0;
    }
}