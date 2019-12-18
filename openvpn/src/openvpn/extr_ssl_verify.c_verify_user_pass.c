#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct user_pass {int /*<<< orphan*/  username; int /*<<< orphan*/  password; } ;
struct tls_session {TYPE_1__* opt; struct key_state* key; } ;
struct tls_multi {int auth_token_state_flags; scalar_t__ auth_token_initial; scalar_t__ auth_token; } ;
struct key_state {int authenticated; int auth_deferred; } ;
struct TYPE_2__ {int ssl_flags; scalar_t__ auth_token_generate; scalar_t__ auth_user_pass_verify_script; int /*<<< orphan*/  plugins; scalar_t__ auth_token_call_auth; } ;

/* Variables and functions */
 int AUTH_TOKEN_EXPIRED ; 
 int AUTH_TOKEN_HMAC_OK ; 
 int /*<<< orphan*/  CC_CRLF ; 
 int /*<<< orphan*/  CC_PRINT ; 
 int /*<<< orphan*/  D_HANDSHAKE ; 
 int /*<<< orphan*/  D_TLS_ERRORS ; 
 int KMDA_DEF ; 
 int KMDA_ERROR ; 
 int KMDA_UNDEF ; 
 size_t KS_PRIMARY ; 
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY ; 
 int OPENVPN_PLUGIN_FUNC_DEFERRED ; 
 int OPENVPN_PLUGIN_FUNC_ERROR ; 
 int OPENVPN_PLUGIN_FUNC_SUCCESS ; 
 int SSLF_USERNAME_AS_COMMON_NAME ; 
 scalar_t__ TLS_USERNAME_LEN ; 
 int /*<<< orphan*/  generate_auth_token (struct user_pass*,struct tls_multi*) ; 
 scalar_t__ is_auth_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  management ; 
 scalar_t__ management_enable_def_auth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ plugin_defined (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_push_reply_auth_token (struct tls_multi*) ; 
 int /*<<< orphan*/  set_common_name (struct tls_session*,int /*<<< orphan*/ ) ; 
 scalar_t__ strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_mod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  string_mod_remap_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ tls_lock_username (struct tls_multi*,int /*<<< orphan*/ ) ; 
 int verify_auth_token (struct user_pass*,struct tls_multi*,struct tls_session*) ; 
 int verify_user_pass_management (struct tls_session*,struct tls_multi*,struct user_pass*) ; 
 int verify_user_pass_plugin (struct tls_session*,struct tls_multi*,struct user_pass*) ; 
 int verify_user_pass_script (struct tls_session*,struct tls_multi*,struct user_pass*) ; 
 int /*<<< orphan*/  wipe_auth_token (struct tls_multi*) ; 

void
verify_user_pass(struct user_pass *up, struct tls_multi *multi,
                 struct tls_session *session)
{
    int s1 = OPENVPN_PLUGIN_FUNC_SUCCESS;
    bool s2 = true;
    struct key_state *ks = &session->key[KS_PRIMARY];      /* primary key */

#ifdef MANAGEMENT_DEF_AUTH
    int man_def_auth = KMDA_UNDEF;

    if (management_enable_def_auth(management))
    {
        man_def_auth = KMDA_DEF;
    }
#endif

    /* enforce character class restrictions in username/password */
    string_mod_remap_name(up->username);
    string_mod(up->password, CC_PRINT, CC_CRLF, '_');

    /*
     * If auth token succeeds we skip the auth
     * methods unless otherwise specified
     */
    bool skip_auth = false;

    /*
     * If server is configured with --auth-gen-token and the client sends
     * something that looks like an authentication token, this
     * round will be done internally using the token instead of
     * calling any external authentication modules.
     */
    if (session->opt->auth_token_generate && is_auth_token(up->password))
    {
        multi->auth_token_state_flags = verify_auth_token(up, multi, session);
        if (session->opt->auth_token_call_auth)
        {
            /*
             * we do not care about the result here because it is
             * the responsibility of the external authentication to
             * decide what to do with the result
             */
        }
        else if (multi->auth_token_state_flags == AUTH_TOKEN_HMAC_OK)
        {
            /*
             * We do not want the EXPIRED or EMPTY USER flags here so check
             * for equality with AUTH_TOKEN_HMAC_OK
             */
            msg(M_WARN, "TLS: Username/auth-token authentication "
                        "succeeded for username '%s'",
                up->username);
              skip_auth = true;
        }
        else
        {
            wipe_auth_token(multi);
            ks->authenticated = false;
            msg(M_WARN, "TLS: Username/auth-token authentication "
                        "failed for username '%s'", up->username);
            return;
        }
    }
    /* call plugin(s) and/or script */
    if (!skip_auth)
    {
#ifdef MANAGEMENT_DEF_AUTH
        if (man_def_auth==KMDA_DEF)
        {
            man_def_auth = verify_user_pass_management(session, multi, up);
        }
#endif
        if (plugin_defined(session->opt->plugins, OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY))
        {
            s1 = verify_user_pass_plugin(session, multi, up);
        }

        if (session->opt->auth_user_pass_verify_script)
        {
            s2 = verify_user_pass_script(session, multi, up);
        }
    }

    /* check sizing of username if it will become our common name */
    if ((session->opt->ssl_flags & SSLF_USERNAME_AS_COMMON_NAME) &&
         strlen(up->username)>TLS_USERNAME_LEN)
    {
        msg(D_TLS_ERRORS,
                "TLS Auth Error: --username-as-common name specified and username is longer than the maximum permitted Common Name length of %d characters",
                TLS_USERNAME_LEN);
        s1 = OPENVPN_PLUGIN_FUNC_ERROR;
    }
    /* auth succeeded? */
    if ((s1 == OPENVPN_PLUGIN_FUNC_SUCCESS
#ifdef PLUGIN_DEF_AUTH
         || s1 == OPENVPN_PLUGIN_FUNC_DEFERRED
#endif
         ) && s2
#ifdef MANAGEMENT_DEF_AUTH
        && man_def_auth != KMDA_ERROR
#endif
        && tls_lock_username(multi, up->username))
    {
        ks->authenticated = true;
#ifdef PLUGIN_DEF_AUTH
        if (s1 == OPENVPN_PLUGIN_FUNC_DEFERRED)
        {
            ks->auth_deferred = true;
        }
#endif
#ifdef MANAGEMENT_DEF_AUTH
        if (man_def_auth != KMDA_UNDEF)
        {
            ks->auth_deferred = true;
        }
#endif
        if ((session->opt->ssl_flags & SSLF_USERNAME_AS_COMMON_NAME))
        {
            set_common_name(session, up->username);
        }

#if P2MP_SERVER
        if ((session->opt->auth_token_generate))
        {
            /*
             * If we accepted a (not expired) token, i.e.
             * initial auth via token on new connection, we need
             * to store the auth-token in multi->auth_token, so
             * the initial timestamp and session id can be extracted from it
             */
            if (multi->auth_token && (multi->auth_token_state_flags & AUTH_TOKEN_HMAC_OK)
                && !(multi->auth_token_state_flags & AUTH_TOKEN_EXPIRED))
            {
                multi->auth_token = strdup(up->password);
            }

            /*
             * Server is configured with --auth-gen-token but no token has yet
             * been generated for this client.  Generate one and save it.
             */
            generate_auth_token(up, multi);
        }
        /*
         * Auth token already sent to client, update auth-token on client.
         * The initial auth-token is sent as part of the push message, for this
         * update we need to schedule an extra push message.
         */
        if (multi->auth_token_initial)
        {
            /*
             * We do not explicitly schedule the sending of the
             * control message here but control message are only
             * postponed when the control channel  is not yet fully
             * established and furthermore since this is called in
             * the middle of authentication, there are other messages
             * (new data channel keys) that are sent anyway and will
             * trigger schedueling
             */
            send_push_reply_auth_token(multi);
        }
#endif
#ifdef ENABLE_DEF_AUTH
        msg(D_HANDSHAKE, "TLS: Username/Password authentication %s for username '%s' %s",
            ks->auth_deferred ? "deferred" : "succeeded",
            up->username,
            (session->opt->ssl_flags & SSLF_USERNAME_AS_COMMON_NAME) ? "[CN SET]" : "");
#else
        msg(D_HANDSHAKE, "TLS: Username/Password authentication %s for username '%s' %s",
            "succeeded",
            up->username,
            (session->opt->ssl_flags & SSLF_USERNAME_AS_COMMON_NAME) ? "[CN SET]" : "");
#endif
    }
    else
    {
        msg(D_TLS_ERRORS, "TLS Auth Error: Auth Username/Password verification failed for peer");
    }
}