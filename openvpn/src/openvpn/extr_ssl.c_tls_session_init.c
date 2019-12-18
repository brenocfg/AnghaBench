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
struct TYPE_5__ {int /*<<< orphan*/  packet_id; int /*<<< orphan*/  pid_persist; } ;
struct TYPE_6__ {TYPE_2__ opt; int /*<<< orphan*/  work; } ;
struct tls_session {int /*<<< orphan*/  session_id; int /*<<< orphan*/ * key; TYPE_3__ tls_wrap; int /*<<< orphan*/  key_id; TYPE_1__* opt; int /*<<< orphan*/  initial_opcode; } ;
struct TYPE_4__ {int key_method; int /*<<< orphan*/  replay_time; int /*<<< orphan*/  replay_window; int /*<<< orphan*/  frame; TYPE_3__ tls_wrap; scalar_t__ tls_crypt_v2; scalar_t__ server; } ;
struct tls_multi {TYPE_1__ opt; } ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BUF_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLEAR (struct tls_session) ; 
 int /*<<< orphan*/  D_TLS_DEBUG ; 
 size_t KS_PRIMARY ; 
 int /*<<< orphan*/  P_CONTROL_HARD_RESET_CLIENT_V1 ; 
 int /*<<< orphan*/  P_CONTROL_HARD_RESET_CLIENT_V2 ; 
 int /*<<< orphan*/  P_CONTROL_HARD_RESET_CLIENT_V3 ; 
 int /*<<< orphan*/  P_CONTROL_HARD_RESET_SERVER_V1 ; 
 int /*<<< orphan*/  P_CONTROL_HARD_RESET_SERVER_V2 ; 
 int /*<<< orphan*/  alloc_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  key_state_init (struct tls_session*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_id_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_id_persist_load_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_id_defined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_id_print (int /*<<< orphan*/ *,struct gc_arena*) ; 
 int /*<<< orphan*/  session_id_random (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tls_session_init(struct tls_multi *multi, struct tls_session *session)
{
    struct gc_arena gc = gc_new();

    dmsg(D_TLS_DEBUG, "TLS: tls_session_init: entry");

    CLEAR(*session);

    /* Set options data to point to parent's option structure */
    session->opt = &multi->opt;

    /* Randomize session # if it is 0 */
    while (!session_id_defined(&session->session_id))
    {
        session_id_random(&session->session_id);
    }

    /* Are we a TLS server or client? */
    ASSERT(session->opt->key_method >= 1);
    if (session->opt->key_method == 1)
    {
        session->initial_opcode = session->opt->server ?
                                  P_CONTROL_HARD_RESET_SERVER_V1 : P_CONTROL_HARD_RESET_CLIENT_V1;
    }
    else /* session->opt->key_method >= 2 */
    {
        if (session->opt->server)
        {
            session->initial_opcode = P_CONTROL_HARD_RESET_SERVER_V2;
        }
        else
        {
            session->initial_opcode = session->opt->tls_crypt_v2 ?
                                      P_CONTROL_HARD_RESET_CLIENT_V3 : P_CONTROL_HARD_RESET_CLIENT_V2;
        }
    }

    /* Initialize control channel authentication parameters */
    session->tls_wrap = session->opt->tls_wrap;
    session->tls_wrap.work = alloc_buf(BUF_SIZE(&session->opt->frame));

    /* initialize packet ID replay window for --tls-auth */
    packet_id_init(&session->tls_wrap.opt.packet_id,
                   session->opt->replay_window,
                   session->opt->replay_time,
                   "TLS_WRAP", session->key_id);

    /* load most recent packet-id to replay protect on --tls-auth */
    packet_id_persist_load_obj(session->tls_wrap.opt.pid_persist,
                               &session->tls_wrap.opt.packet_id);

    key_state_init(session, &session->key[KS_PRIMARY]);

    dmsg(D_TLS_DEBUG, "TLS: tls_session_init: new session object, sid=%s",
         session_id_print(&session->session_id, &gc));

    gc_free(&gc);
}