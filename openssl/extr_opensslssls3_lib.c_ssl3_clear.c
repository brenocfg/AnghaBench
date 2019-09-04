#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pkey; int /*<<< orphan*/ * peer_cert_sigalgs; int /*<<< orphan*/ * peer_sigalgs; int /*<<< orphan*/  pmslen; int /*<<< orphan*/  pms; int /*<<< orphan*/ * ciphers_raw; int /*<<< orphan*/  peer_ca_names; int /*<<< orphan*/ * ctype; } ;
struct TYPE_12__ {int /*<<< orphan*/ * alpn_proposed; int /*<<< orphan*/ * alpn_selected; int /*<<< orphan*/  peer_tmp; TYPE_1__ tmp; } ;
struct TYPE_10__ {scalar_t__ npn_len; int /*<<< orphan*/ * npn; } ;
struct TYPE_11__ {TYPE_2__ ext; int /*<<< orphan*/  version; TYPE_8__ s3; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL3_VERSION ; 
 int /*<<< orphan*/  X509_NAME_free ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sk_X509_NAME_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl3_cleanup_key_block (TYPE_3__*) ; 
 int /*<<< orphan*/  ssl3_free_digest_list (TYPE_3__*) ; 
 int /*<<< orphan*/  ssl_free_wbio_buffer (TYPE_3__*) ; 

int ssl3_clear(SSL *s)
{
    ssl3_cleanup_key_block(s);
    OPENSSL_free(s->s3.tmp.ctype);
    sk_X509_NAME_pop_free(s->s3.tmp.peer_ca_names, X509_NAME_free);
    OPENSSL_free(s->s3.tmp.ciphers_raw);
    OPENSSL_clear_free(s->s3.tmp.pms, s->s3.tmp.pmslen);
    OPENSSL_free(s->s3.tmp.peer_sigalgs);
    OPENSSL_free(s->s3.tmp.peer_cert_sigalgs);

#if !defined(OPENSSL_NO_EC) || !defined(OPENSSL_NO_DH)
    EVP_PKEY_free(s->s3.tmp.pkey);
    EVP_PKEY_free(s->s3.peer_tmp);
#endif                          /* !OPENSSL_NO_EC */

    ssl3_free_digest_list(s);

    OPENSSL_free(s->s3.alpn_selected);
    OPENSSL_free(s->s3.alpn_proposed);

    /* NULL/zero-out everything in the s3 struct */
    memset(&s->s3, 0, sizeof(s->s3));

    if (!ssl_free_wbio_buffer(s))
        return 0;

    s->version = SSL3_VERSION;

#if !defined(OPENSSL_NO_NEXTPROTONEG)
    OPENSSL_free(s->ext.npn);
    s->ext.npn = NULL;
    s->ext.npn_len = 0;
#endif

    return 1;
}