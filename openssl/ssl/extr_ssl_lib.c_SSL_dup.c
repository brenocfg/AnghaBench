#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int /*<<< orphan*/  client_ca_names; int /*<<< orphan*/  ca_names; int /*<<< orphan*/ * cipher_list_by_id; int /*<<< orphan*/ * cipher_list; int /*<<< orphan*/  param; int /*<<< orphan*/  default_passwd_callback_userdata; int /*<<< orphan*/  default_passwd_callback; int /*<<< orphan*/  hit; int /*<<< orphan*/  shutdown; scalar_t__ server; scalar_t__ handshake_func; int /*<<< orphan*/ * rbio; int /*<<< orphan*/ * wbio; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  generate_session_id; int /*<<< orphan*/  msg_callback_arg; int /*<<< orphan*/  msg_callback; int /*<<< orphan*/  mode; int /*<<< orphan*/  options; int /*<<< orphan*/  version; scalar_t__ sid_ctx_length; int /*<<< orphan*/  sid_ctx; int /*<<< orphan*/ * cert; int /*<<< orphan*/  method; int /*<<< orphan*/ * session; int /*<<< orphan*/  lock; int /*<<< orphan*/  references; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_dup_state (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BIO_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_SSL ; 
 int /*<<< orphan*/  CRYPTO_UP_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_dup_ex_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_copy_session_id (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_get_SSL_CTX (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_get_info_callback (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_get_max_cert_list (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_get_read_ahead (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_get_verify_callback (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_get_verify_depth (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_get_verify_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_in_before (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_in_init (TYPE_1__*) ; 
 TYPE_1__* SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_accept_state (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_set_connect_state (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_set_info_callback (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_max_cert_list (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_read_ahead (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_session_id_context (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_set_ssl_method (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_verify (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_verify_depth (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_inherit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup_ca_names (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* sk_SSL_CIPHER_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ssl_cert_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_cert_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_dane_dup (TYPE_1__*,TYPE_1__*) ; 

SSL *SSL_dup(SSL *s)
{
    SSL *ret;
    int i;

    /* If we're not quiescent, just up_ref! */
    if (!SSL_in_init(s) || !SSL_in_before(s)) {
        CRYPTO_UP_REF(&s->references, &i, s->lock);
        return s;
    }

    /*
     * Otherwise, copy configuration state, and session if set.
     */
    if ((ret = SSL_new(SSL_get_SSL_CTX(s))) == NULL)
        return NULL;

    if (s->session != NULL) {
        /*
         * Arranges to share the same session via up_ref.  This "copies"
         * session-id, SSL_METHOD, sid_ctx, and 'cert'
         */
        if (!SSL_copy_session_id(ret, s))
            goto err;
    } else {
        /*
         * No session has been established yet, so we have to expect that
         * s->cert or ret->cert will be changed later -- they should not both
         * point to the same object, and thus we can't use
         * SSL_copy_session_id.
         */
        if (!SSL_set_ssl_method(ret, s->method))
            goto err;

        if (s->cert != NULL) {
            ssl_cert_free(ret->cert);
            ret->cert = ssl_cert_dup(s->cert);
            if (ret->cert == NULL)
                goto err;
        }

        if (!SSL_set_session_id_context(ret, s->sid_ctx,
                                        (int)s->sid_ctx_length))
            goto err;
    }

    if (!ssl_dane_dup(ret, s))
        goto err;
    ret->version = s->version;
    ret->options = s->options;
    ret->mode = s->mode;
    SSL_set_max_cert_list(ret, SSL_get_max_cert_list(s));
    SSL_set_read_ahead(ret, SSL_get_read_ahead(s));
    ret->msg_callback = s->msg_callback;
    ret->msg_callback_arg = s->msg_callback_arg;
    SSL_set_verify(ret, SSL_get_verify_mode(s), SSL_get_verify_callback(s));
    SSL_set_verify_depth(ret, SSL_get_verify_depth(s));
    ret->generate_session_id = s->generate_session_id;

    SSL_set_info_callback(ret, SSL_get_info_callback(s));

    /* copy app data, a little dangerous perhaps */
    if (!CRYPTO_dup_ex_data(CRYPTO_EX_INDEX_SSL, &ret->ex_data, &s->ex_data))
        goto err;

    /* setup rbio, and wbio */
    if (s->rbio != NULL) {
        if (!BIO_dup_state(s->rbio, (char *)&ret->rbio))
            goto err;
    }
    if (s->wbio != NULL) {
        if (s->wbio != s->rbio) {
            if (!BIO_dup_state(s->wbio, (char *)&ret->wbio))
                goto err;
        } else {
            BIO_up_ref(ret->rbio);
            ret->wbio = ret->rbio;
        }
    }

    ret->server = s->server;
    if (s->handshake_func) {
        if (s->server)
            SSL_set_accept_state(ret);
        else
            SSL_set_connect_state(ret);
    }
    ret->shutdown = s->shutdown;
    ret->hit = s->hit;

    ret->default_passwd_callback = s->default_passwd_callback;
    ret->default_passwd_callback_userdata = s->default_passwd_callback_userdata;

    X509_VERIFY_PARAM_inherit(ret->param, s->param);

    /* dup the cipher_list and cipher_list_by_id stacks */
    if (s->cipher_list != NULL) {
        if ((ret->cipher_list = sk_SSL_CIPHER_dup(s->cipher_list)) == NULL)
            goto err;
    }
    if (s->cipher_list_by_id != NULL)
        if ((ret->cipher_list_by_id = sk_SSL_CIPHER_dup(s->cipher_list_by_id))
            == NULL)
            goto err;

    /* Dup the client_CA list */
    if (!dup_ca_names(&ret->ca_names, s->ca_names)
            || !dup_ca_names(&ret->client_ca_names, s->client_ca_names))
        goto err;

    return ret;

 err:
    SSL_free(ret);
    return NULL;
}