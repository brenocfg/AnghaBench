#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  secure; TYPE_2__* alpn; TYPE_2__* supportedgroups; TYPE_2__* ecpointformats; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_1__ ext; int /*<<< orphan*/  client_cert_engine; int /*<<< orphan*/  srtp_profiles; int /*<<< orphan*/ * comp_methods; int /*<<< orphan*/  extra_certs; int /*<<< orphan*/  client_ca_names; int /*<<< orphan*/  ca_names; int /*<<< orphan*/  cert; int /*<<< orphan*/  tls13_ciphersuites; int /*<<< orphan*/  cipher_list_by_id; int /*<<< orphan*/  cipher_list; int /*<<< orphan*/  ctlog_store; int /*<<< orphan*/  cert_store; int /*<<< orphan*/ * sessions; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  dane; int /*<<< orphan*/  param; int /*<<< orphan*/  references; } ;
typedef  TYPE_2__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_SSL_CTX ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CTLOG_STORE_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 int /*<<< orphan*/  OPENSSL_secure_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  REF_PRINT_COUNT (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_CTX_SRP_CTX_free (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_CTX_flush_sessions (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_free ; 
 int /*<<< orphan*/  X509_STORE_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free ; 
 int /*<<< orphan*/  dane_ctx_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lh_SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_SRTP_PROTECTION_PROFILE_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_SSL_CIPHER_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_NAME_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_cert_free (int /*<<< orphan*/ ) ; 

void SSL_CTX_free(SSL_CTX *a)
{
    int i;

    if (a == NULL)
        return;

    CRYPTO_DOWN_REF(&a->references, &i, a->lock);
    REF_PRINT_COUNT("SSL_CTX", a);
    if (i > 0)
        return;
    REF_ASSERT_ISNT(i < 0);

    X509_VERIFY_PARAM_free(a->param);
    dane_ctx_final(&a->dane);

    /*
     * Free internal session cache. However: the remove_cb() may reference
     * the ex_data of SSL_CTX, thus the ex_data store can only be removed
     * after the sessions were flushed.
     * As the ex_data handling routines might also touch the session cache,
     * the most secure solution seems to be: empty (flush) the cache, then
     * free ex_data, then finally free the cache.
     * (See ticket [openssl.org #212].)
     */
    if (a->sessions != NULL)
        SSL_CTX_flush_sessions(a, 0);

    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_SSL_CTX, a, &a->ex_data);
    lh_SSL_SESSION_free(a->sessions);
    X509_STORE_free(a->cert_store);
#ifndef OPENSSL_NO_CT
    CTLOG_STORE_free(a->ctlog_store);
#endif
    sk_SSL_CIPHER_free(a->cipher_list);
    sk_SSL_CIPHER_free(a->cipher_list_by_id);
    sk_SSL_CIPHER_free(a->tls13_ciphersuites);
    ssl_cert_free(a->cert);
    sk_X509_NAME_pop_free(a->ca_names, X509_NAME_free);
    sk_X509_NAME_pop_free(a->client_ca_names, X509_NAME_free);
    sk_X509_pop_free(a->extra_certs, X509_free);
    a->comp_methods = NULL;
#ifndef OPENSSL_NO_SRTP
    sk_SRTP_PROTECTION_PROFILE_free(a->srtp_profiles);
#endif
#ifndef OPENSSL_NO_SRP
    SSL_CTX_SRP_CTX_free(a);
#endif
#ifndef OPENSSL_NO_ENGINE
    ENGINE_finish(a->client_cert_engine);
#endif

#ifndef OPENSSL_NO_EC
    OPENSSL_free(a->ext.ecpointformats);
#endif
    OPENSSL_free(a->ext.supportedgroups);
    OPENSSL_free(a->ext.alpn);
    OPENSSL_secure_free(a->ext.secure);

    CRYPTO_THREAD_lock_free(a->lock);

    OPENSSL_free(a);
}