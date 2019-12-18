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
struct link_socket_info {int connection_established; scalar_t__ ipchange_command; int /*<<< orphan*/  plugins; TYPE_1__* lsa; } ;
struct link_socket_actual {int dummy; } ;
struct gc_arena {int dummy; } ;
struct env_set {int dummy; } ;
struct buffer {int dummy; } ;
struct argv {int dummy; } ;
struct TYPE_2__ {struct link_socket_actual actual; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR (struct buffer*) ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  M_WARN ; 
 scalar_t__ OPENVPN_PLUGIN_FUNC_SUCCESS ; 
 int /*<<< orphan*/  OPENVPN_PLUGIN_IPCHANGE ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,char const*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  ipchange_fmt (int,struct argv*,struct link_socket_info*,struct gc_arena*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  openvpn_run_script (struct argv*,struct env_set*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ plugin_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct argv*,int /*<<< orphan*/ *,struct env_set*) ; 
 scalar_t__ plugin_defined (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* print_link_socket_actual (struct link_socket_actual*,struct gc_arena*) ; 
 int /*<<< orphan*/  setenv_str (struct env_set*,char*,char const*) ; 
 int /*<<< orphan*/  setenv_trusted (struct env_set*,struct link_socket_info*) ; 

void
link_socket_connection_initiated(const struct buffer *buf,
                                 struct link_socket_info *info,
                                 const struct link_socket_actual *act,
                                 const char *common_name,
                                 struct env_set *es)
{
    struct gc_arena gc = gc_new();

    info->lsa->actual = *act; /* Note: skip this line for --force-dest */
    setenv_trusted(es, info);
    info->connection_established = true;

    /* Print connection initiated message, with common name if available */
    {
        struct buffer out = alloc_buf_gc(256, &gc);
        if (common_name)
        {
            buf_printf(&out, "[%s] ", common_name);
        }
        buf_printf(&out, "Peer Connection Initiated with %s", print_link_socket_actual(&info->lsa->actual, &gc));
        msg(M_INFO, "%s", BSTR(&out));
    }

    /* set environmental vars */
    setenv_str(es, "common_name", common_name);

    /* Process --ipchange plugin */
    if (plugin_defined(info->plugins, OPENVPN_PLUGIN_IPCHANGE))
    {
        struct argv argv = argv_new();
        ipchange_fmt(false, &argv, info, &gc);
        if (plugin_call(info->plugins, OPENVPN_PLUGIN_IPCHANGE, &argv, NULL, es) != OPENVPN_PLUGIN_FUNC_SUCCESS)
        {
            msg(M_WARN, "WARNING: ipchange plugin call failed");
        }
        argv_reset(&argv);
    }

    /* Process --ipchange option */
    if (info->ipchange_command)
    {
        struct argv argv = argv_new();
        setenv_str(es, "script_type", "ipchange");
        ipchange_fmt(true, &argv, info, &gc);
        openvpn_run_script(&argv, es, 0, "--ipchange");
        argv_reset(&argv);
    }

    gc_free(&gc);
}