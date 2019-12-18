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
struct management_callback {int /*<<< orphan*/  network_change; int /*<<< orphan*/  remote_cmd; int /*<<< orphan*/  proxy_cmd; int /*<<< orphan*/  show_net; int /*<<< orphan*/  status; struct context* arg; } ;
struct context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct management_callback) ; 
 scalar_t__ management ; 
 int /*<<< orphan*/  management_callback_network_change ; 
 int /*<<< orphan*/  management_callback_proxy_cmd ; 
 int /*<<< orphan*/  management_callback_remote_cmd ; 
 int /*<<< orphan*/  management_callback_status_p2p ; 
 int /*<<< orphan*/  management_set_callback (scalar_t__,struct management_callback*) ; 
 int /*<<< orphan*/  management_show_net_callback ; 

void
init_management_callback_p2p(struct context *c)
{
#ifdef ENABLE_MANAGEMENT
    if (management)
    {
        struct management_callback cb;
        CLEAR(cb);
        cb.arg = c;
        cb.status = management_callback_status_p2p;
        cb.show_net = management_show_net_callback;
        cb.proxy_cmd = management_callback_proxy_cmd;
        cb.remote_cmd = management_callback_remote_cmd;
#ifdef TARGET_ANDROID
        cb.network_change = management_callback_network_change;
#endif
        management_set_callback(management, &cb);
    }
#endif
}