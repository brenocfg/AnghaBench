#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int management_flags; int mode; int /*<<< orphan*/  writepid; } ;
struct context {int first_time; scalar_t__ signal_received; int /*<<< orphan*/  net_ctx; int /*<<< orphan*/  gc; TYPE_1__ options; int /*<<< orphan*/  es; struct context* sig; int /*<<< orphan*/  did_we_daemonize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR (struct context) ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 scalar_t__ IS_SIG (struct context*) ; 
 int /*<<< orphan*/  IVM_LEVEL_1 ; 
 int MF_QUERY_PASSWORDS ; 
#define  MODE_POINT_TO_POINT 129 
#define  MODE_SERVER 128 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  M_USAGE ; 
 int /*<<< orphan*/  OPENVPN_EXIT_STATUS_GOOD ; 
 int /*<<< orphan*/  OPENVPN_PLUGIN_INIT_PRE_CONFIG_PARSE ; 
 int /*<<< orphan*/  OPT_P_DEFAULT ; 
 scalar_t__ SIGHUP ; 
 scalar_t__ SIGUSR1 ; 
 int /*<<< orphan*/  SetConsoleOutputCP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_management () ; 
 int /*<<< orphan*/  context_clear_all_except_first_time (struct context*) ; 
 int /*<<< orphan*/  context_gc_free (struct context*) ; 
 int /*<<< orphan*/  context_init_1 (struct context*) ; 
 scalar_t__ do_genkey (TYPE_1__*) ; 
 scalar_t__ do_persist_tuntap (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ do_test_crypto (TYPE_1__*) ; 
 int /*<<< orphan*/  env_set_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  env_set_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_management () ; 
 int /*<<< orphan*/  init_options (TYPE_1__*,int) ; 
 int /*<<< orphan*/  init_options_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  init_plugins (struct context*) ; 
 int /*<<< orphan*/  init_query_passwords (struct context*) ; 
 scalar_t__ init_static () ; 
 int /*<<< orphan*/  init_verb_mute (struct context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_ctx_init (struct context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_management (struct context*) ; 
 int /*<<< orphan*/  open_plugins (struct context*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openvpn_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  options_postprocess (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_argv (TYPE_1__*,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  possibly_become_daemon (TYPE_1__*) ; 
 int /*<<< orphan*/  pre_init_signal_catch () ; 
 int /*<<< orphan*/  pre_setup (TYPE_1__*) ; 
 scalar_t__ print_openssl_info (TYPE_1__*) ; 
 int /*<<< orphan*/  print_signal (struct context*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_win_sys_path_via_env (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv_settings (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  show_library_versions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_settings (TYPE_1__*) ; 
 int /*<<< orphan*/  show_windows_version (int /*<<< orphan*/ ) ; 
 struct context siginfo_static ; 
 int /*<<< orphan*/  signal_restart_status (struct context*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  title_string ; 
 int /*<<< orphan*/  tunnel_point_to_point (struct context*) ; 
 int /*<<< orphan*/  tunnel_server (struct context*) ; 
 int /*<<< orphan*/  uninit_options (TYPE_1__*) ; 
 int /*<<< orphan*/  uninit_static () ; 
 int /*<<< orphan*/  write_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int
openvpn_main(int argc, char *argv[])
{
    struct context c;

#if PEDANTIC
    fprintf(stderr, "Sorry, I was built with --enable-pedantic and I am incapable of doing any real work!\n");
    return 1;
#endif

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    CLEAR(c);

    /* signify first time for components which can
     * only be initialized once per program instantiation. */
    c.first_time = true;

    /* initialize program-wide statics */
    if (init_static())
    {
        /*
         * This loop is initially executed on startup and then
         * once per SIGHUP.
         */
        do
        {
            /* enter pre-initialization mode with regard to signal handling */
            pre_init_signal_catch();

            /* zero context struct but leave first_time member alone */
            context_clear_all_except_first_time(&c);

            /* static signal info object */
            CLEAR(siginfo_static);
            c.sig = &siginfo_static;

            /* initialize garbage collector scoped to context object */
            gc_init(&c.gc);

            /* initialize environmental variable store */
            c.es = env_set_create(NULL);
#ifdef _WIN32
            set_win_sys_path_via_env(c.es);
#endif

#ifdef ENABLE_MANAGEMENT
            /* initialize management subsystem */
            init_management();
#endif

            /* initialize options to default state */
            init_options(&c.options, true);

            /* parse command line options, and read configuration file */
            parse_argv(&c.options, argc, argv, M_USAGE, OPT_P_DEFAULT, NULL, c.es);

#ifdef ENABLE_PLUGIN
            /* plugins may contribute options configuration */
            init_verb_mute(&c, IVM_LEVEL_1);
            init_plugins(&c);
            open_plugins(&c, true, OPENVPN_PLUGIN_INIT_PRE_CONFIG_PARSE);
#endif

            net_ctx_init(&c, &c.net_ctx);

            /* init verbosity and mute levels */
            init_verb_mute(&c, IVM_LEVEL_1);

            /* set dev options */
            init_options_dev(&c.options);

            /* openssl print info? */
            if (print_openssl_info(&c.options))
            {
                break;
            }

            /* --genkey mode? */
            if (do_genkey(&c.options))
            {
                break;
            }

            /* tun/tap persist command? */
            if (do_persist_tuntap(&c.options, &c.net_ctx))
            {
                break;
            }

            /* sanity check on options */
            options_postprocess(&c.options);

            /* show all option settings */
            show_settings(&c.options);

            /* print version number */
            msg(M_INFO, "%s", title_string);
#ifdef _WIN32
            show_windows_version(M_INFO);
#endif
            show_library_versions(M_INFO);

            /* misc stuff */
            pre_setup(&c.options);

            /* test crypto? */
            if (do_test_crypto(&c.options))
            {
                break;
            }

            /* Query passwords before becoming a daemon if we don't use the
             * management interface to get them. */
#ifdef ENABLE_MANAGEMENT
            if (!(c.options.management_flags & MF_QUERY_PASSWORDS))
#endif
            init_query_passwords(&c);

            /* become a daemon if --daemon */
            if (c.first_time)
            {
                c.did_we_daemonize = possibly_become_daemon(&c.options);
                write_pid(c.options.writepid);
            }

#ifdef ENABLE_MANAGEMENT
            /* open management subsystem */
            if (!open_management(&c))
            {
                break;
            }
            /* query for passwords through management interface, if needed */
            if (c.options.management_flags & MF_QUERY_PASSWORDS)
            {
                init_query_passwords(&c);
            }
#endif

            /* set certain options as environmental variables */
            setenv_settings(c.es, &c.options);

            /* finish context init */
            context_init_1(&c);

            do
            {
                /* run tunnel depending on mode */
                switch (c.options.mode)
                {
                    case MODE_POINT_TO_POINT:
                        tunnel_point_to_point(&c);
                        break;

#if P2MP_SERVER
                    case MODE_SERVER:
                        tunnel_server(&c);
                        break;

#endif
                    default:
                        ASSERT(0);
                }

                /* indicates first iteration -- has program-wide scope */
                c.first_time = false;

                /* any signals received? */
                if (IS_SIG(&c))
                {
                    print_signal(c.sig, NULL, M_INFO);
                }

                /* pass restart status to management subsystem */
                signal_restart_status(c.sig);
            }
            while (c.sig->signal_received == SIGUSR1);

            env_set_destroy(c.es);
            uninit_options(&c.options);
            gc_reset(&c.gc);
            net_ctx_free(&c.net_ctx);
        }
        while (c.sig->signal_received == SIGHUP);
    }

    context_gc_free(&c);

#ifdef ENABLE_MANAGEMENT
    /* close management interface */
    close_management();
#endif

    /* uninitialize program-wide statics */
    uninit_static();

    openvpn_exit(OPENVPN_EXIT_STATUS_GOOD); /* exit point */
    return 0;                               /* NOTREACHED */
}