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
struct tuntap {int dummy; } ;
struct route_list {int dummy; } ;
struct route_ipv6_list {int dummy; } ;
struct plugin_list {int dummy; } ;
struct options {scalar_t__ show_net_up; scalar_t__ route_script; int /*<<< orphan*/  route_noexec; } ;
struct env_set {int dummy; } ;
struct argv {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;

/* Variables and functions */
 int D_SHOW_NET ; 
 int M_INFO ; 
 int M_NOPREFIX ; 
 int /*<<< orphan*/  M_WARN ; 
 scalar_t__ OPENVPN_PLUGIN_FUNC_SUCCESS ; 
 int /*<<< orphan*/  OPENVPN_PLUGIN_ROUTE_UP ; 
 int /*<<< orphan*/  ROUTE_OPTION_FLAGS (struct options const*) ; 
 int /*<<< orphan*/  add_routes (struct route_list*,struct route_ipv6_list*,struct tuntap const*,int /*<<< orphan*/ ,struct env_set*,int /*<<< orphan*/ *) ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_parse_cmd (struct argv*,scalar_t__) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 scalar_t__ check_debug_level (int) ; 
 scalar_t__ management ; 
 int /*<<< orphan*/  management_up_down (scalar_t__,char*,struct env_set*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  openvpn_run_script (struct argv*,struct env_set*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ plugin_call (struct plugin_list const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct env_set*) ; 
 scalar_t__ plugin_defined (struct plugin_list const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  route_did_redirect_default_gateway (struct route_list*) ; 
 int /*<<< orphan*/  setenv_int (struct env_set*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv_str (struct env_set*,char*,char*) ; 
 int /*<<< orphan*/  show_adapters (int) ; 
 int /*<<< orphan*/  show_routes (int) ; 

void
do_route(const struct options *options,
         struct route_list *route_list,
         struct route_ipv6_list *route_ipv6_list,
         const struct tuntap *tt,
         const struct plugin_list *plugins,
         struct env_set *es,
         openvpn_net_ctx_t *ctx)
{
    if (!options->route_noexec && ( route_list || route_ipv6_list ) )
    {
        add_routes(route_list, route_ipv6_list, tt, ROUTE_OPTION_FLAGS(options),
                   es, ctx);
        setenv_int(es, "redirect_gateway", route_did_redirect_default_gateway(route_list));
    }
#ifdef ENABLE_MANAGEMENT
    if (management)
    {
        management_up_down(management, "UP", es);
    }
#endif

    if (plugin_defined(plugins, OPENVPN_PLUGIN_ROUTE_UP))
    {
        if (plugin_call(plugins, OPENVPN_PLUGIN_ROUTE_UP, NULL, NULL, es) != OPENVPN_PLUGIN_FUNC_SUCCESS)
        {
            msg(M_WARN, "WARNING: route-up plugin call failed");
        }
    }

    if (options->route_script)
    {
        struct argv argv = argv_new();
        setenv_str(es, "script_type", "route-up");
        argv_parse_cmd(&argv, options->route_script);
        openvpn_run_script(&argv, es, 0, "--route-up");
        argv_reset(&argv);
    }

#ifdef _WIN32
    if (options->show_net_up)
    {
        show_routes(M_INFO|M_NOPREFIX);
        show_adapters(M_INFO|M_NOPREFIX);
    }
    else if (check_debug_level(D_SHOW_NET))
    {
        show_routes(D_SHOW_NET|M_NOPREFIX);
        show_adapters(D_SHOW_NET|M_NOPREFIX);
    }
#endif
}