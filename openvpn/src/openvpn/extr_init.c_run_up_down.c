#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct plugin_list {int dummy; } ;
struct gc_arena {int dummy; } ;
struct env_set {int dummy; } ;
struct argv {int dummy; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (char const*) ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  M_INFO ; 
 scalar_t__ OPENVPN_PLUGIN_FUNC_SUCCESS ; 
 int /*<<< orphan*/  S_FATAL ; 
 int /*<<< orphan*/  argv_msg (int /*<<< orphan*/ ,struct argv*) ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_parse_cmd (struct argv*,char const*) ; 
 int /*<<< orphan*/  argv_printf (struct argv*,char*,char const*,int,int,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  argv_printf_cat (struct argv*,char*,char const*,int,int,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  openvpn_run_script (struct argv*,struct env_set*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ plugin_call (struct plugin_list const*,int,struct argv*,int /*<<< orphan*/ *,struct env_set*) ; 
 scalar_t__ plugin_defined (struct plugin_list const*,int) ; 
 int /*<<< orphan*/  setenv_int (struct env_set*,char*,int) ; 
 int /*<<< orphan*/  setenv_str (struct env_set*,char*,char const*) ; 

__attribute__((used)) static void
run_up_down(const char *command,
            const struct plugin_list *plugins,
            int plugin_type,
            const char *arg,
#ifdef _WIN32
            DWORD adapter_index,
#endif
            const char *dev_type,
            int tun_mtu,
            int link_mtu,
            const char *ifconfig_local,
            const char *ifconfig_remote,
            const char *context,
            const char *signal_text,
            const char *script_type,
            struct env_set *es)
{
    struct gc_arena gc = gc_new();

    if (signal_text)
    {
        setenv_str(es, "signal", signal_text);
    }
    setenv_str(es, "script_context", context);
    setenv_int(es, "tun_mtu", tun_mtu);
    setenv_int(es, "link_mtu", link_mtu);
    setenv_str(es, "dev", arg);
    if (dev_type)
    {
        setenv_str(es, "dev_type", dev_type);
    }
#ifdef _WIN32
    setenv_int(es, "dev_idx", adapter_index);
#endif

    if (!ifconfig_local)
    {
        ifconfig_local = "";
    }
    if (!ifconfig_remote)
    {
        ifconfig_remote = "";
    }
    if (!context)
    {
        context = "";
    }

    if (plugin_defined(plugins, plugin_type))
    {
        struct argv argv = argv_new();
        ASSERT(arg);
        argv_printf(&argv,
                    "%s %d %d %s %s %s",
                    arg,
                    tun_mtu, link_mtu,
                    ifconfig_local, ifconfig_remote,
                    context);

        if (plugin_call(plugins, plugin_type, &argv, NULL, es) != OPENVPN_PLUGIN_FUNC_SUCCESS)
        {
            msg(M_FATAL, "ERROR: up/down plugin call failed");
        }

        argv_reset(&argv);
    }

    if (command)
    {
        struct argv argv = argv_new();
        ASSERT(arg);
        setenv_str(es, "script_type", script_type);
        argv_parse_cmd(&argv, command);
        argv_printf_cat(&argv, "%s %d %d %s %s %s", arg, tun_mtu, link_mtu,
                        ifconfig_local, ifconfig_remote, context);
        argv_msg(M_INFO, &argv);
        openvpn_run_script(&argv, es, S_FATAL, "--up/--down");
        argv_reset(&argv);
    }

    gc_free(&gc);
}