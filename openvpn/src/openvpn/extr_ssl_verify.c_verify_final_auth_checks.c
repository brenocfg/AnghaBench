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
struct tls_session {char* common_name; TYPE_1__* opt; struct cert_hash_set* cert_hash_set; struct key_state* key; } ;
struct tls_multi {char* locked_cn; scalar_t__ locked_cert_hash_set; } ;
struct key_state {int authenticated; } ;
struct gc_arena {int dummy; } ;
struct cert_hash_set {int dummy; } ;
struct TYPE_2__ {scalar_t__ client_config_dir_exclusive; } ;

/* Variables and functions */
 char* CCD_DEFAULT ; 
 int /*<<< orphan*/  D_TLS_ERRORS ; 
 size_t KS_PRIMARY ; 
 int /*<<< orphan*/  cert_hash_compare (struct cert_hash_set const*,scalar_t__) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* platform_gen_path (scalar_t__,char const*,struct gc_arena*) ; 
 int /*<<< orphan*/  platform_test_file (char const*) ; 
 int /*<<< orphan*/  set_common_name (struct tls_session*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  tls_deauthenticate (struct tls_multi*) ; 
 int /*<<< orphan*/  wipe_auth_token (struct tls_multi*) ; 

void
verify_final_auth_checks(struct tls_multi *multi, struct tls_session *session)
{
    struct key_state *ks = &session->key[KS_PRIMARY];      /* primary key */

    /* While it shouldn't really happen, don't allow the common name to be NULL */
    if (!session->common_name)
    {
        set_common_name(session, "");
    }

    /* Don't allow the CN to change once it's been locked */
    if (ks->authenticated && multi->locked_cn)
    {
        const char *cn = session->common_name;
        if (cn && strcmp(cn, multi->locked_cn))
        {
            msg(D_TLS_ERRORS, "TLS Auth Error: TLS object CN attempted to change from '%s' to '%s' -- tunnel disabled",
                multi->locked_cn,
                cn);

            /* change the common name back to its original value and disable the tunnel */
            set_common_name(session, multi->locked_cn);
            tls_deauthenticate(multi);
        }
    }

    /* Don't allow the cert hashes to change once they have been locked */
    if (ks->authenticated && multi->locked_cert_hash_set)
    {
        const struct cert_hash_set *chs = session->cert_hash_set;
        if (chs && !cert_hash_compare(chs, multi->locked_cert_hash_set))
        {
            msg(D_TLS_ERRORS, "TLS Auth Error: TLS object CN=%s client-provided SSL certs unexpectedly changed during mid-session reauth",
                session->common_name);

            /* disable the tunnel */
            tls_deauthenticate(multi);
        }
    }

    /* verify --client-config-dir based authentication */
    if (ks->authenticated && session->opt->client_config_dir_exclusive)
    {
        struct gc_arena gc = gc_new();

        const char *cn = session->common_name;
        const char *path = platform_gen_path(session->opt->client_config_dir_exclusive,
                                             cn, &gc);
        if (!cn || !strcmp(cn, CCD_DEFAULT) || !platform_test_file(path))
        {
            ks->authenticated = false;
            wipe_auth_token(multi);
            msg(D_TLS_ERRORS, "TLS Auth Error: --client-config-dir authentication failed for common name '%s' file='%s'",
                session->common_name,
                path ? path : "UNDEF");
        }

        gc_free(&gc);
    }
}