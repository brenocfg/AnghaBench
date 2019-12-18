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
struct TYPE_2__ {int /*<<< orphan*/  gc; int /*<<< orphan*/  pf; int /*<<< orphan*/  mda_context; int /*<<< orphan*/ * comp_context; } ;
struct context {scalar_t__ mode; TYPE_1__ c2; } ;

/* Variables and functions */
 scalar_t__ CM_CHILD_TCP ; 
 scalar_t__ CM_CHILD_UDP ; 
 scalar_t__ CM_P2P ; 
 scalar_t__ CM_TOP ; 
 int /*<<< orphan*/  comp_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_close_check_if_restart_permitted (struct context*) ; 
 int /*<<< orphan*/  do_close_event_set (struct context*) ; 
 int /*<<< orphan*/  do_close_fragment (struct context*) ; 
 int /*<<< orphan*/  do_close_free_buf (struct context*) ; 
 int /*<<< orphan*/  do_close_free_key_schedule (struct context*,int) ; 
 int /*<<< orphan*/  do_close_ifconfig_pool_persist (struct context*) ; 
 int /*<<< orphan*/  do_close_link_socket (struct context*) ; 
 int /*<<< orphan*/  do_close_packet_id (struct context*) ; 
 int /*<<< orphan*/  do_close_plugins (struct context*) ; 
 int /*<<< orphan*/  do_close_status_output (struct context*) ; 
 int /*<<< orphan*/  do_close_tls (struct context*) ; 
 int /*<<< orphan*/  do_close_tun (struct context*,int) ; 
 int /*<<< orphan*/  do_env_set_destroy (struct context*) ; 
 int /*<<< orphan*/  gc_free (int /*<<< orphan*/ *) ; 
 scalar_t__ management ; 
 int /*<<< orphan*/  management_notify_client_close (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_destroy_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_ncp_options (struct context*) ; 
 int /*<<< orphan*/  uninit_proxy (struct context*) ; 

void
close_instance(struct context *c)
{
    /* close event objects */
    do_close_event_set(c);

    if (c->mode == CM_P2P
        || c->mode == CM_CHILD_TCP
        || c->mode == CM_CHILD_UDP
        || c->mode == CM_TOP)
    {
        /* if xinetd/inetd mode, don't allow restart */
        do_close_check_if_restart_permitted(c);

#ifdef USE_COMP
        if (c->c2.comp_context)
        {
            comp_uninit(c->c2.comp_context);
            c->c2.comp_context = NULL;
        }
#endif

        /* free buffers */
        do_close_free_buf(c);

        /* close TLS */
        do_close_tls(c);

        /* free key schedules */
        do_close_free_key_schedule(c, (c->mode == CM_P2P || c->mode == CM_TOP));

        restore_ncp_options(c);

        /* close TCP/UDP connection */
        do_close_link_socket(c);

        /* close TUN/TAP device */
        do_close_tun(c, false);

#ifdef MANAGEMENT_DEF_AUTH
        if (management)
        {
            management_notify_client_close(management, &c->c2.mda_context, NULL);
        }
#endif

#ifdef ENABLE_PF
        pf_destroy_context(&c->c2.pf);
#endif

#ifdef ENABLE_PLUGIN
        /* call plugin close functions and unload */
        do_close_plugins(c);
#endif

        /* close packet-id persistence file */
        do_close_packet_id(c);

        /* close --status file */
        do_close_status_output(c);

#ifdef ENABLE_FRAGMENT
        /* close fragmentation handler */
        do_close_fragment(c);
#endif

        /* close --ifconfig-pool-persist obj */
        do_close_ifconfig_pool_persist(c);

        /* free up environmental variable store */
        do_env_set_destroy(c);

        /* close HTTP or SOCKS proxy */
        uninit_proxy(c);

        /* garbage collect */
        gc_free(&c->c2.gc);
    }
}