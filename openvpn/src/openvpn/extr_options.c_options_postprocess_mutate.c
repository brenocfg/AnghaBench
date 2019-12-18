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
struct remote_list {int len; struct remote_entry** array; } ;
struct remote_entry {struct connection_entry* remote; } ;
struct connection_entry {int len; int /*<<< orphan*/ * array; } ;
struct options {int ncp_enabled; scalar_t__ mode; scalar_t__ http_proxy_override; scalar_t__ pull; int /*<<< orphan*/ * dh_file; scalar_t__ tls_server; struct connection_entry* connection_list; struct connection_entry ce; struct remote_list* remote_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct connection_entry*) ; 
 scalar_t__ MODE_SERVER ; 
 int /*<<< orphan*/  M_USAGE ; 
 int /*<<< orphan*/  M_WARN ; 
 struct connection_entry* alloc_connection_entry (struct options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connection_entry_load_re (struct connection_entry*,struct remote_entry const*) ; 
 int /*<<< orphan*/  helper_client_server (struct options*) ; 
 int /*<<< orphan*/  helper_keepalive (struct options*) ; 
 int /*<<< orphan*/  helper_tcp_nodelay (struct options*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  notnull (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  options_postprocess_http_proxy_override (struct options*) ; 
 int /*<<< orphan*/  options_postprocess_mutate_ce (struct options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  options_postprocess_mutate_invariant (struct options*) ; 
 int /*<<< orphan*/  pre_pull_save (struct options*) ; 
 scalar_t__ streq (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
options_postprocess_mutate(struct options *o)
{
    int i;
    /*
     * Process helper-type options which map to other, more complex
     * sequences of options.
     */
    helper_client_server(o);
    helper_keepalive(o);
    helper_tcp_nodelay(o);

    options_postprocess_mutate_invariant(o);

    if (o->remote_list && !o->connection_list)
    {
        /*
         * Convert remotes into connection list
         */
        const struct remote_list *rl = o->remote_list;
        for (i = 0; i < rl->len; ++i)
        {
            const struct remote_entry *re = rl->array[i];
            struct connection_entry ce = o->ce;
            struct connection_entry *ace;

            ASSERT(re->remote);
            connection_entry_load_re(&ce, re);
            ace = alloc_connection_entry(o, M_USAGE);
            ASSERT(ace);
            *ace = ce;
        }
    }
    else if (!o->remote_list && !o->connection_list)
    {
        struct connection_entry *ace;
        ace = alloc_connection_entry(o, M_USAGE);
        ASSERT(ace);
        *ace = o->ce;
    }

    ASSERT(o->connection_list);
    for (i = 0; i < o->connection_list->len; ++i)
    {
        options_postprocess_mutate_ce(o, o->connection_list->array[i]);
    }

    if (o->tls_server)
    {
        /* Check that DH file is specified, or explicitly disabled */
        notnull(o->dh_file, "DH file (--dh)");
        if (streq(o->dh_file, "none"))
        {
            o->dh_file = NULL;
        }
    }
    else if (o->dh_file)
    {
        /* DH file is only meaningful in a tls-server context. */
        msg(M_WARN, "WARNING: Ignoring option 'dh' in tls-client mode, please only "
            "include this in your server configuration");
        o->dh_file = NULL;
    }

    /* cipher negotiation (NCP) currently assumes --pull or --mode server */
    if (o->ncp_enabled
        && !(o->pull || o->mode == MODE_SERVER) )
    {
        msg( M_WARN, "disabling NCP mode (--ncp-disable) because not "
             "in P2MP client or server mode" );
        o->ncp_enabled = false;
    }

#if ENABLE_MANAGEMENT
    if (o->http_proxy_override)
    {
        options_postprocess_http_proxy_override(o);
    }
#endif

#if P2MP
    /*
     * Save certain parms before modifying options via --pull
     */
    pre_pull_save(o);
#endif
}