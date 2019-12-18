#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tls_session {struct key_state* key; int /*<<< orphan*/  session_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  gremlin; int /*<<< orphan*/  single_session; } ;
struct link_socket_actual {int dummy; } ;
struct tls_multi {int /*<<< orphan*/  n_soft_errors; int /*<<< orphan*/  n_hard_errors; TYPE_3__** key_scan; TYPE_2__ opt; struct tls_session* session; struct link_socket_actual to_link_addr; } ;
struct link_socket_info {TYPE_1__* lsa; } ;
struct key_state {scalar_t__ state; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  session_id_remote; } ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  interval_t ;
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_4__ {int /*<<< orphan*/  actual; } ;

/* Variables and functions */
 scalar_t__ DECRYPT_KEY_ENABLED (struct tls_multi*,struct key_state*) ; 
 int /*<<< orphan*/  D_TLS_DEBUG ; 
 int /*<<< orphan*/  D_TLS_DEBUG_LOW ; 
 int GREMLIN_CONNECTION_FLOOD_LEVEL (int /*<<< orphan*/ ) ; 
 size_t KS_LAME_DUCK ; 
 size_t KS_PRIMARY ; 
 int /*<<< orphan*/  PERF_TLS_MULTI_PROCESS ; 
 scalar_t__ SIZE (TYPE_3__**) ; 
 scalar_t__ S_ACTIVE ; 
 scalar_t__ S_ERROR ; 
 scalar_t__ S_INITIAL ; 
 int TLSMP_ACTIVE ; 
 int TLSMP_INACTIVE ; 
 int TLSMP_KILL ; 
 int TLS_AUTHENTICATION_FAILED ; 
 int TLS_AUTHENTICATION_SUCCEEDED ; 
 int /*<<< orphan*/  TLS_MULTI_AUTH_STATUS_INTERVAL ; 
 int TM_ACTIVE ; 
 size_t TM_LAME_DUCK ; 
 int TM_SIZE ; 
 size_t TM_UNTRUSTED ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 scalar_t__ lame_duck_must_die (struct tls_session*,int /*<<< orphan*/ *) ; 
 scalar_t__ link_socket_actual_defined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_session (struct tls_multi*,int,size_t,int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  perf_pop () ; 
 int /*<<< orphan*/  perf_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_link_socket_actual (int /*<<< orphan*/ *,struct gc_arena*) ; 
 int /*<<< orphan*/  reset_session (struct tls_multi*,struct tls_session*) ; 
 int /*<<< orphan*/  session_id_print (int /*<<< orphan*/ *,struct gc_arena*) ; 
 int /*<<< orphan*/  state_name (scalar_t__) ; 
 int tls_authentication_status (struct tls_multi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_clear_error () ; 
 scalar_t__ tls_process (struct tls_multi*,struct tls_session*,struct buffer*,struct link_socket_actual**,struct link_socket_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_session_free (struct tls_session*,int) ; 
 int /*<<< orphan*/  update_time () ; 

int
tls_multi_process(struct tls_multi *multi,
                  struct buffer *to_link,
                  struct link_socket_actual **to_link_addr,
                  struct link_socket_info *to_link_socket_info,
                  interval_t *wakeup)
{
    struct gc_arena gc = gc_new();
    int i;
    int active = TLSMP_INACTIVE;
    bool error = false;
    int tas;

    perf_push(PERF_TLS_MULTI_PROCESS);

    tls_clear_error();

    /*
     * Process each session object having state of S_INITIAL or greater,
     * and which has a defined remote IP addr.
     */

    for (i = 0; i < TM_SIZE; ++i)
    {
        struct tls_session *session = &multi->session[i];
        struct key_state *ks = &session->key[KS_PRIMARY];
        struct key_state *ks_lame = &session->key[KS_LAME_DUCK];

        /* set initial remote address */
        if (i == TM_ACTIVE && ks->state == S_INITIAL
            && link_socket_actual_defined(&to_link_socket_info->lsa->actual))
        {
            ks->remote_addr = to_link_socket_info->lsa->actual;
        }

        dmsg(D_TLS_DEBUG,
             "TLS: tls_multi_process: i=%d state=%s, mysid=%s, stored-sid=%s, stored-ip=%s",
             i,
             state_name(ks->state),
             session_id_print(&session->session_id, &gc),
             session_id_print(&ks->session_id_remote, &gc),
             print_link_socket_actual(&ks->remote_addr, &gc));

        if (ks->state >= S_INITIAL && link_socket_actual_defined(&ks->remote_addr))
        {
            struct link_socket_actual *tla = NULL;

            update_time();

            if (tls_process(multi, session, to_link, &tla,
                            to_link_socket_info, wakeup))
            {
                active = TLSMP_ACTIVE;
            }

            /*
             * If tls_process produced an outgoing packet,
             * return the link_socket_actual object (which
             * contains the outgoing address).
             */
            if (tla)
            {
                multi->to_link_addr = *tla;
                *to_link_addr = &multi->to_link_addr;
            }

            /*
             * If tls_process hits an error:
             * (1) If the session has an unexpired lame duck key, preserve it.
             * (2) Reinitialize the session.
             * (3) Increment soft error count
             */
            if (ks->state == S_ERROR)
            {
                ++multi->n_soft_errors;

                if (i == TM_ACTIVE)
                {
                    error = true;
                }

                if (i == TM_ACTIVE
                    && ks_lame->state >= S_ACTIVE
                    && !multi->opt.single_session)
                {
                    move_session(multi, TM_LAME_DUCK, TM_ACTIVE, true);
                }
                else
                {
                    reset_session(multi, session);
                }
            }
        }
    }

    update_time();

    tas = tls_authentication_status(multi, TLS_MULTI_AUTH_STATUS_INTERVAL);

    /*
     * If lame duck session expires, kill it.
     */
    if (lame_duck_must_die(&multi->session[TM_LAME_DUCK], wakeup))
    {
        tls_session_free(&multi->session[TM_LAME_DUCK], true);
        msg(D_TLS_DEBUG_LOW, "TLS: tls_multi_process: killed expiring key");
    }

    /*
     * If untrusted session achieves TLS authentication,
     * move it to active session, usurping any prior session.
     *
     * A semi-trusted session is one in which the certificate authentication
     * succeeded (if cert verification is enabled) but the username/password
     * verification failed.  A semi-trusted session can forward data on the
     * TLS control channel but not on the tunnel channel.
     */
    if (DECRYPT_KEY_ENABLED(multi, &multi->session[TM_UNTRUSTED].key[KS_PRIMARY]))
    {
        move_session(multi, TM_ACTIVE, TM_UNTRUSTED, true);
        msg(D_TLS_DEBUG_LOW, "TLS: tls_multi_process: untrusted session promoted to %strusted",
            tas == TLS_AUTHENTICATION_SUCCEEDED ? "" : "semi-");
    }

    /*
     * A hard error means that TM_ACTIVE hit an S_ERROR state and that no
     * other key state objects are S_ACTIVE or higher.
     */
    if (error)
    {
        for (i = 0; i < (int) SIZE(multi->key_scan); ++i)
        {
            if (multi->key_scan[i]->state >= S_ACTIVE)
            {
                goto nohard;
            }
        }
        ++multi->n_hard_errors;
    }
nohard:

#ifdef ENABLE_DEBUG
    /* DEBUGGING -- flood peer with repeating connection attempts */
    {
        const int throw_level = GREMLIN_CONNECTION_FLOOD_LEVEL(multi->opt.gremlin);
        if (throw_level)
        {
            for (i = 0; i < (int) SIZE(multi->key_scan); ++i)
            {
                if (multi->key_scan[i]->state >= throw_level)
                {
                    ++multi->n_hard_errors;
                    ++multi->n_soft_errors;
                }
            }
        }
    }
#endif

    perf_pop();
    gc_free(&gc);

    return (tas == TLS_AUTHENTICATION_FAILED) ? TLSMP_KILL : active;
}