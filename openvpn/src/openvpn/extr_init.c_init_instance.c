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
struct TYPE_5__ {scalar_t__ proto; scalar_t__ fragment; } ;
struct options {scalar_t__ up_delay; TYPE_2__ ce; int /*<<< orphan*/  comp; scalar_t__ mlock; scalar_t__ resolve_in_advance; } ;
struct env_set {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  did_open_tun; int /*<<< orphan*/  frame; int /*<<< orphan*/  frame_initial; int /*<<< orphan*/  comp_context; int /*<<< orphan*/  fragment; int /*<<< orphan*/  occ_op; int /*<<< orphan*/  gc; } ;
struct context {scalar_t__ mode; TYPE_1__* sig; scalar_t__ first_time; TYPE_3__ c2; struct options options; } ;
struct TYPE_4__ {char* signal_text; int /*<<< orphan*/  source; scalar_t__ signal_received; } ;

/* Variables and functions */
 scalar_t__ AR_INTERACT ; 
 unsigned int CF_INIT_TLS_AUTH_STANDALONE ; 
 unsigned int CF_INIT_TLS_MULTI ; 
 unsigned int CF_LOAD_PERSISTED_PACKET_ID ; 
 scalar_t__ CM_CHILD_TCP ; 
 scalar_t__ CM_CHILD_UDP ; 
 scalar_t__ CM_P2P ; 
 scalar_t__ CM_TOP ; 
 scalar_t__ IS_SIG (struct context*) ; 
 int /*<<< orphan*/  IVM_LEVEL_2 ; 
 int LS_MODE_DEFAULT ; 
 int LS_MODE_TCP_ACCEPT_FROM ; 
 int LS_MODE_TCP_LISTEN ; 
 int /*<<< orphan*/  OPENVPN_PLUGIN_INIT_POST_DAEMON ; 
 int /*<<< orphan*/  OPENVPN_PLUGIN_INIT_POST_UID_CHANGE ; 
 int /*<<< orphan*/  OPENVPN_PLUGIN_INIT_PRE_DAEMON ; 
 int /*<<< orphan*/  P2P_ERROR_DELAY_MS ; 
 scalar_t__ PROTO_TCP_SERVER ; 
 scalar_t__ PULL_DEFINED (struct options const*) ; 
 int SHAPER_DEFINED (struct options*) ; 
 int /*<<< orphan*/  SIG_SOURCE_SOFT ; 
 scalar_t__ auth_retry_get () ; 
 int /*<<< orphan*/  close_context (struct context*,int,unsigned int const) ; 
 scalar_t__ comp_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comp_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_compute_occ_strings (struct context*) ; 
 int /*<<< orphan*/  do_event_set_init (struct context*,int) ; 
 int /*<<< orphan*/  do_inherit_env (struct context*,struct env_set const*) ; 
 int /*<<< orphan*/  do_init_buffers (struct context*) ; 
 int /*<<< orphan*/  do_init_crypto (struct context*,unsigned int) ; 
 int /*<<< orphan*/  do_init_first_time (struct context*) ; 
 int /*<<< orphan*/  do_init_fragment (struct context*) ; 
 int /*<<< orphan*/  do_init_frame (struct context*) ; 
 int /*<<< orphan*/  do_init_frame_tls (struct context*) ; 
 int /*<<< orphan*/  do_init_server_poll_timeout (struct context*) ; 
 int /*<<< orphan*/  do_init_socket_1 (struct context*,int) ; 
 int /*<<< orphan*/  do_init_socket_2 (struct context*) ; 
 int /*<<< orphan*/  do_init_timers (struct context*,int) ; 
 int /*<<< orphan*/  do_init_traffic_shaper (struct context*) ; 
 int /*<<< orphan*/  do_link_socket_new (struct context*) ; 
 int /*<<< orphan*/  do_open_ifconfig_pool_persist (struct context*) ; 
 int /*<<< orphan*/  do_open_status_output (struct context*) ; 
 int /*<<< orphan*/  do_open_tun (struct context*) ; 
 int /*<<< orphan*/  do_option_warnings (struct context*) ; 
 int /*<<< orphan*/  do_preresolve (struct context*) ; 
 int /*<<< orphan*/  do_print_data_channel_mtu_parms (struct context*) ; 
 int /*<<< orphan*/  do_setup_fast_io (struct context*) ; 
 int /*<<< orphan*/  do_signal_on_tls_errors (struct context*) ; 
 int /*<<< orphan*/  do_startup_pause (struct context*) ; 
 int /*<<< orphan*/  do_uid_gid_chroot (struct context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fragment_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_init_mssfix (int /*<<< orphan*/ *,struct options*) ; 
 int /*<<< orphan*/  gc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_management_callback_p2p (struct context*) ; 
 int /*<<< orphan*/  init_port_share (struct context*) ; 
 int /*<<< orphan*/  init_proxy (struct context*) ; 
 int /*<<< orphan*/  init_query_passwords (struct context*) ; 
 int /*<<< orphan*/  init_verb_mute (struct context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_connection_entry (struct context*) ; 
 int /*<<< orphan*/  occ_reset_op () ; 
 int /*<<< orphan*/  open_plugins (struct context*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_init_context (struct context*) ; 
 int /*<<< orphan*/  platform_mlockall (int) ; 
 int /*<<< orphan*/  set_check_status_error_delay (int /*<<< orphan*/ ) ; 

void
init_instance(struct context *c, const struct env_set *env, const unsigned int flags)
{
    const struct options *options = &c->options;
    const bool child = (c->mode == CM_CHILD_TCP || c->mode == CM_CHILD_UDP);
    int link_socket_mode = LS_MODE_DEFAULT;

    /* init garbage collection level */
    gc_init(&c->c2.gc);

    /* inherit environmental variables */
    if (env)
    {
        do_inherit_env(c, env);
    }

    /* signals caught here will abort */
    c->sig->signal_received = 0;
    c->sig->signal_text = NULL;
    c->sig->source = SIG_SOURCE_SOFT;

    if (c->mode == CM_P2P)
    {
        init_management_callback_p2p(c);
    }

    /* possible sleep or management hold if restart */
    if (c->mode == CM_P2P || c->mode == CM_TOP)
    {
        do_startup_pause(c);
        if (IS_SIG(c))
        {
            goto sig;
        }
    }

    if (c->options.resolve_in_advance)
    {
        do_preresolve(c);
        if (IS_SIG(c))
        {
            goto sig;
        }
    }

    /* map in current connection entry */
    next_connection_entry(c);

    /* link_socket_mode allows CM_CHILD_TCP
     * instances to inherit acceptable fds
     * from a top-level parent */
    if (c->options.ce.proto == PROTO_TCP_SERVER)
    {
        if (c->mode == CM_TOP)
        {
            link_socket_mode = LS_MODE_TCP_LISTEN;
        }
        else if (c->mode == CM_CHILD_TCP)
        {
            link_socket_mode = LS_MODE_TCP_ACCEPT_FROM;
        }
    }

    /* should we disable paging? */
    if (c->first_time && options->mlock)
    {
        platform_mlockall(true);
    }

#if P2MP
    /* get passwords if undefined */
    if (auth_retry_get() == AR_INTERACT)
    {
        init_query_passwords(c);
    }
#endif

    /* initialize context level 2 --verb/--mute parms */
    init_verb_mute(c, IVM_LEVEL_2);

    /* set error message delay for non-server modes */
    if (c->mode == CM_P2P)
    {
        set_check_status_error_delay(P2P_ERROR_DELAY_MS);
    }

    /* warn about inconsistent options */
    if (c->mode == CM_P2P || c->mode == CM_TOP)
    {
        do_option_warnings(c);
    }

#ifdef ENABLE_PLUGIN
    /* initialize plugins */
    if (c->mode == CM_P2P || c->mode == CM_TOP)
    {
        open_plugins(c, false, OPENVPN_PLUGIN_INIT_PRE_DAEMON);
    }
#endif

    /* should we enable fast I/O? */
    if (c->mode == CM_P2P || c->mode == CM_TOP)
    {
        do_setup_fast_io(c);
    }

    /* should we throw a signal on TLS errors? */
    do_signal_on_tls_errors(c);

    /* open --status file */
    if (c->mode == CM_P2P || c->mode == CM_TOP)
    {
        do_open_status_output(c);
    }

    /* open --ifconfig-pool-persist file */
    if (c->mode == CM_TOP)
    {
        do_open_ifconfig_pool_persist(c);
    }

#ifdef ENABLE_OCC
    /* reset OCC state */
    if (c->mode == CM_P2P || child)
    {
        c->c2.occ_op = occ_reset_op();
    }
#endif

    /* our wait-for-i/o objects, different for posix vs. win32 */
    if (c->mode == CM_P2P)
    {
        do_event_set_init(c, SHAPER_DEFINED(&c->options));
    }
    else if (c->mode == CM_CHILD_TCP)
    {
        do_event_set_init(c, false);
    }

    /* initialize HTTP or SOCKS proxy object at scope level 2 */
    init_proxy(c);

    /* allocate our socket object */
    if (c->mode == CM_P2P || c->mode == CM_TOP || c->mode == CM_CHILD_TCP)
    {
        do_link_socket_new(c);
    }

#ifdef ENABLE_FRAGMENT
    /* initialize internal fragmentation object */
    if (options->ce.fragment && (c->mode == CM_P2P || child))
    {
        c->c2.fragment = fragment_init(&c->c2.frame);
    }
#endif

    /* init crypto layer */
    {
        unsigned int crypto_flags = 0;
        if (c->mode == CM_TOP)
        {
            crypto_flags = CF_INIT_TLS_AUTH_STANDALONE;
        }
        else if (c->mode == CM_P2P)
        {
            crypto_flags = CF_LOAD_PERSISTED_PACKET_ID | CF_INIT_TLS_MULTI;
        }
        else if (child)
        {
            crypto_flags = CF_INIT_TLS_MULTI;
        }
        do_init_crypto(c, crypto_flags);
        if (IS_SIG(c) && !child)
        {
            goto sig;
        }
    }

#ifdef USE_COMP
    /* initialize compression library. */
    if (comp_enabled(&options->comp) && (c->mode == CM_P2P || child))
    {
        c->c2.comp_context = comp_init(&options->comp);
    }
#endif

    /* initialize MTU variables */
    do_init_frame(c);

    /* initialize TLS MTU variables */
    do_init_frame_tls(c);

    /* init workspace buffers whose size is derived from frame size */
    if (c->mode == CM_P2P || c->mode == CM_CHILD_TCP)
    {
        do_init_buffers(c);
    }

#ifdef ENABLE_FRAGMENT
    /* initialize internal fragmentation capability with known frame size */
    if (options->ce.fragment && (c->mode == CM_P2P || child))
    {
        do_init_fragment(c);
    }
#endif

    /* initialize dynamic MTU variable */
    frame_init_mssfix(&c->c2.frame, &c->options);

    /* bind the TCP/UDP socket */
    if (c->mode == CM_P2P || c->mode == CM_TOP || c->mode == CM_CHILD_TCP)
    {
        do_init_socket_1(c, link_socket_mode);
    }

    /* initialize tun/tap device object,
     * open tun/tap device, ifconfig, run up script, etc. */
    if (!(options->up_delay || PULL_DEFINED(options)) && (c->mode == CM_P2P || c->mode == CM_TOP))
    {
        c->c2.did_open_tun = do_open_tun(c);
    }

    c->c2.frame_initial = c->c2.frame;

    /* print MTU info */
    do_print_data_channel_mtu_parms(c);

#ifdef ENABLE_OCC
    /* get local and remote options compatibility strings */
    if (c->mode == CM_P2P || child)
    {
        do_compute_occ_strings(c);
    }
#endif

    /* initialize output speed limiter */
    if (c->mode == CM_P2P)
    {
        do_init_traffic_shaper(c);
    }

    /* do one-time inits, and possibly become a daemon here */
    do_init_first_time(c);

#ifdef ENABLE_PLUGIN
    /* initialize plugins */
    if (c->mode == CM_P2P || c->mode == CM_TOP)
    {
        open_plugins(c, false, OPENVPN_PLUGIN_INIT_POST_DAEMON);
    }
#endif

    /* initialise connect timeout timer */
    do_init_server_poll_timeout(c);

    /* finalize the TCP/UDP socket */
    if (c->mode == CM_P2P || c->mode == CM_TOP || c->mode == CM_CHILD_TCP)
    {
        do_init_socket_2(c);
    }

    /*
     * Actually do UID/GID downgrade, and chroot, if requested.
     * May be delayed by --client, --pull, or --up-delay.
     */
    do_uid_gid_chroot(c, c->c2.did_open_tun);

    /* initialize timers */
    if (c->mode == CM_P2P || child)
    {
        do_init_timers(c, false);
    }

#ifdef ENABLE_PLUGIN
    /* initialize plugins */
    if (c->mode == CM_P2P || c->mode == CM_TOP)
    {
        open_plugins(c, false, OPENVPN_PLUGIN_INIT_POST_UID_CHANGE);
    }
#endif

#if PORT_SHARE
    /* share OpenVPN port with foreign (such as HTTPS) server */
    if (c->first_time && (c->mode == CM_P2P || c->mode == CM_TOP))
    {
        init_port_share(c);
    }
#endif

#ifdef ENABLE_PF
    if (child)
    {
        pf_init_context(c);
    }
#endif

    /* Check for signals */
    if (IS_SIG(c))
    {
        goto sig;
    }

    return;

sig:
    if (!c->sig->signal_text)
    {
        c->sig->signal_text = "init_instance";
    }
    close_context(c, -1, flags);
    return;
}