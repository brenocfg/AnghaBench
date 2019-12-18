#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct connection_entry {int flags; } ;
struct TYPE_8__ {int no_advance; int unsuccessful_attempts; int connect_retry_max; struct connection_entry ce; int /*<<< orphan*/  persist_remote_ip; struct connection_list* connection_list; } ;
struct TYPE_6__ {TYPE_1__* remote_list; TYPE_1__* current_remote; } ;
struct TYPE_7__ {TYPE_2__ link_socket_addr; } ;
struct context {TYPE_4__ options; TYPE_3__ c1; } ;
struct connection_list {size_t current; size_t len; struct connection_entry** array; } ;
struct TYPE_5__ {struct TYPE_5__* ai_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int CE_DISABLED ; 
 scalar_t__ IS_SIG (struct context*) ; 
 int /*<<< orphan*/  M_FATAL ; 
 int ce_management_query_proxy (struct context*) ; 
 int ce_management_query_remote (struct context*) ; 
 scalar_t__ management ; 
 scalar_t__ management_query_proxy_enabled (scalar_t__) ; 
 scalar_t__ management_query_remote_enabled (scalar_t__) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  update_options_ce_post (TYPE_4__*) ; 

__attribute__((used)) static void
next_connection_entry(struct context *c)
{
    struct connection_list *l = c->options.connection_list;
    bool ce_defined;
    struct connection_entry *ce;
    int n_cycles = 0;

    do
    {
        ce_defined = true;
        if (c->options.no_advance && l->current >= 0)
        {
            c->options.no_advance = false;
        }
        else
        {
            /* Check if there is another resolved address to try for
             * the current connection */
            if (c->c1.link_socket_addr.current_remote
                && c->c1.link_socket_addr.current_remote->ai_next)
            {
                c->c1.link_socket_addr.current_remote =
                    c->c1.link_socket_addr.current_remote->ai_next;
            }
            else
            {
                /* FIXME (schwabe) fix the persist-remote-ip option for real,
                 * this is broken probably ever since connection lists and multiple
                 * remote existed
                 */
                if (!c->options.persist_remote_ip)
                {
                    /* close_instance should have cleared the addrinfo objects */
                    ASSERT(c->c1.link_socket_addr.current_remote == NULL);
                    ASSERT(c->c1.link_socket_addr.remote_list == NULL);
                }
                else
                {
                    c->c1.link_socket_addr.current_remote =
                        c->c1.link_socket_addr.remote_list;
                }

                /*
                 * Increase the number of connection attempts
                 * If this is connect-retry-max * size(l)
                 * OpenVPN will quit
                 */

                c->options.unsuccessful_attempts++;

                if (++l->current >= l->len)
                {

                    l->current = 0;
                    if (++n_cycles >= 2)
                    {
                        msg(M_FATAL, "No usable connection profiles are present");
                    }
                }
            }
        }

        ce = l->array[l->current];

        if (ce->flags & CE_DISABLED)
        {
            ce_defined = false;
        }

        c->options.ce = *ce;
#ifdef ENABLE_MANAGEMENT
        if (ce_defined && management && management_query_remote_enabled(management))
        {
            /* allow management interface to override connection entry details */
            ce_defined = ce_management_query_remote(c);
            if (IS_SIG(c))
            {
                break;
            }
        }
        else if (ce_defined && management && management_query_proxy_enabled(management))
        {
            ce_defined = ce_management_query_proxy(c);
            if (IS_SIG(c))
            {
                break;
            }
        }
#endif
    } while (!ce_defined);

    /* Check if this connection attempt would bring us over the limit */
    if (c->options.connect_retry_max > 0
        && c->options.unsuccessful_attempts > (l->len  * c->options.connect_retry_max))
    {
        msg(M_FATAL, "All connections have been connect-retry-max (%d) times unsuccessful, exiting",
            c->options.connect_retry_max);
    }
    update_options_ce_post(&c->options);
}