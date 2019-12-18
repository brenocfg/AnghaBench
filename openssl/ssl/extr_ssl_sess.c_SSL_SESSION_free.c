#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  alpn_selected; int /*<<< orphan*/  tick; int /*<<< orphan*/  hostname; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ticket_appdata; TYPE_1__ ext; int /*<<< orphan*/  srp_username; int /*<<< orphan*/  psk_identity; int /*<<< orphan*/  psk_identity_hint; int /*<<< orphan*/  peer_chain; int /*<<< orphan*/  peer; int /*<<< orphan*/  session_id; int /*<<< orphan*/  master_key; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  references; } ;
typedef  TYPE_2__ SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_SSL_SESSION ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  REF_PRINT_COUNT (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 

void SSL_SESSION_free(SSL_SESSION *ss)
{
    int i;

    if (ss == NULL)
        return;
    CRYPTO_DOWN_REF(&ss->references, &i, ss->lock);
    REF_PRINT_COUNT("SSL_SESSION", ss);
    if (i > 0)
        return;
    REF_ASSERT_ISNT(i < 0);

    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_SSL_SESSION, ss, &ss->ex_data);

    OPENSSL_cleanse(ss->master_key, sizeof(ss->master_key));
    OPENSSL_cleanse(ss->session_id, sizeof(ss->session_id));
    X509_free(ss->peer);
    sk_X509_pop_free(ss->peer_chain, X509_free);
    OPENSSL_free(ss->ext.hostname);
    OPENSSL_free(ss->ext.tick);
#ifndef OPENSSL_NO_PSK
    OPENSSL_free(ss->psk_identity_hint);
    OPENSSL_free(ss->psk_identity);
#endif
#ifndef OPENSSL_NO_SRP
    OPENSSL_free(ss->srp_username);
#endif
    OPENSSL_free(ss->ext.alpn_selected);
    OPENSSL_free(ss->ticket_appdata);
    CRYPTO_THREAD_lock_free(ss->lock);
    OPENSSL_clear_free(ss, sizeof(*ss));
}