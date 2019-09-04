#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ecpointformats_len; int supportedgroups_len; int ticklen; int alpn_selected_len; int /*<<< orphan*/ * alpn_selected; scalar_t__ tick_lifetime_hint; int /*<<< orphan*/ * tick; int /*<<< orphan*/ * supportedgroups; int /*<<< orphan*/ * ecpointformats; int /*<<< orphan*/ * hostname; } ;
struct TYPE_11__ {int references; int ticket_appdata_len; int /*<<< orphan*/ * ticket_appdata; int /*<<< orphan*/ * srp_username; TYPE_1__ ext; int /*<<< orphan*/  ex_data; int /*<<< orphan*/ * ciphers; int /*<<< orphan*/ * psk_identity; int /*<<< orphan*/ * psk_identity_hint; int /*<<< orphan*/ * peer_chain; int /*<<< orphan*/ * peer; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * next; int /*<<< orphan*/ * prev; } ;
typedef  TYPE_2__ SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_SSL_SESSION ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  CRYPTO_dup_ex_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_2__* OPENSSL_malloc (int) ; 
 void* OPENSSL_memdup (int /*<<< orphan*/ *,int) ; 
 void* OPENSSL_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_F_SSL_SESSION_DUP ; 
 int /*<<< orphan*/  SSL_SESSION_free (TYPE_2__*) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_chain_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sk_SSL_CIPHER_dup (int /*<<< orphan*/ *) ; 

SSL_SESSION *ssl_session_dup(const SSL_SESSION *src, int ticket)
{
    SSL_SESSION *dest;

    dest = OPENSSL_malloc(sizeof(*src));
    if (dest == NULL) {
        goto err;
    }
    memcpy(dest, src, sizeof(*dest));

    /*
     * Set the various pointers to NULL so that we can call SSL_SESSION_free in
     * the case of an error whilst halfway through constructing dest
     */
#ifndef OPENSSL_NO_PSK
    dest->psk_identity_hint = NULL;
    dest->psk_identity = NULL;
#endif
    dest->ciphers = NULL;
    dest->ext.hostname = NULL;
#ifndef OPENSSL_NO_EC
    dest->ext.ecpointformats = NULL;
    dest->ext.supportedgroups = NULL;
#endif
    dest->ext.tick = NULL;
    dest->ext.alpn_selected = NULL;
#ifndef OPENSSL_NO_SRP
    dest->srp_username = NULL;
#endif
    dest->peer_chain = NULL;
    dest->peer = NULL;
    dest->ticket_appdata = NULL;
    memset(&dest->ex_data, 0, sizeof(dest->ex_data));

    /* We deliberately don't copy the prev and next pointers */
    dest->prev = NULL;
    dest->next = NULL;

    dest->references = 1;

    dest->lock = CRYPTO_THREAD_lock_new();
    if (dest->lock == NULL)
        goto err;

    if (!CRYPTO_new_ex_data(CRYPTO_EX_INDEX_SSL_SESSION, dest, &dest->ex_data))
        goto err;

    if (src->peer != NULL) {
        if (!X509_up_ref(src->peer))
            goto err;
        dest->peer = src->peer;
    }

    if (src->peer_chain != NULL) {
        dest->peer_chain = X509_chain_up_ref(src->peer_chain);
        if (dest->peer_chain == NULL)
            goto err;
    }
#ifndef OPENSSL_NO_PSK
    if (src->psk_identity_hint) {
        dest->psk_identity_hint = OPENSSL_strdup(src->psk_identity_hint);
        if (dest->psk_identity_hint == NULL) {
            goto err;
        }
    }
    if (src->psk_identity) {
        dest->psk_identity = OPENSSL_strdup(src->psk_identity);
        if (dest->psk_identity == NULL) {
            goto err;
        }
    }
#endif

    if (src->ciphers != NULL) {
        dest->ciphers = sk_SSL_CIPHER_dup(src->ciphers);
        if (dest->ciphers == NULL)
            goto err;
    }

    if (!CRYPTO_dup_ex_data(CRYPTO_EX_INDEX_SSL_SESSION,
                            &dest->ex_data, &src->ex_data)) {
        goto err;
    }

    if (src->ext.hostname) {
        dest->ext.hostname = OPENSSL_strdup(src->ext.hostname);
        if (dest->ext.hostname == NULL) {
            goto err;
        }
    }
#ifndef OPENSSL_NO_EC
    if (src->ext.ecpointformats) {
        dest->ext.ecpointformats =
            OPENSSL_memdup(src->ext.ecpointformats,
                           src->ext.ecpointformats_len);
        if (dest->ext.ecpointformats == NULL)
            goto err;
    }
    if (src->ext.supportedgroups) {
        dest->ext.supportedgroups =
            OPENSSL_memdup(src->ext.supportedgroups,
                           src->ext.supportedgroups_len
                                * sizeof(*src->ext.supportedgroups));
        if (dest->ext.supportedgroups == NULL)
            goto err;
    }
#endif

    if (ticket != 0 && src->ext.tick != NULL) {
        dest->ext.tick =
            OPENSSL_memdup(src->ext.tick, src->ext.ticklen);
        if (dest->ext.tick == NULL)
            goto err;
    } else {
        dest->ext.tick_lifetime_hint = 0;
        dest->ext.ticklen = 0;
    }

    if (src->ext.alpn_selected != NULL) {
        dest->ext.alpn_selected = OPENSSL_memdup(src->ext.alpn_selected,
                                                 src->ext.alpn_selected_len);
        if (dest->ext.alpn_selected == NULL)
            goto err;
    }

#ifndef OPENSSL_NO_SRP
    if (src->srp_username) {
        dest->srp_username = OPENSSL_strdup(src->srp_username);
        if (dest->srp_username == NULL) {
            goto err;
        }
    }
#endif

    if (src->ticket_appdata != NULL) {
        dest->ticket_appdata =
            OPENSSL_memdup(src->ticket_appdata, src->ticket_appdata_len);
        if (dest->ticket_appdata == NULL)
            goto err;
    }

    return dest;
 err:
    SSLerr(SSL_F_SSL_SESSION_DUP, ERR_R_MALLOC_FAILURE);
    SSL_SESSION_free(dest);
    return NULL;
}