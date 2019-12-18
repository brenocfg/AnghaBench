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
struct web_client {int dummy; } ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */
 int check_host_and_call (int /*<<< orphan*/ *,struct web_client*,char*,int (*) (int /*<<< orphan*/ *,struct web_client*,char*)) ; 
 int /*<<< orphan*/  web_client_can_access_dashboard (struct web_client*) ; 
 int web_client_permission_denied (struct web_client*) ; 

__attribute__((used)) static inline int check_host_and_dashboard_acl_and_call(RRDHOST *host, struct web_client *w, char *url, int (*func)(RRDHOST *, struct web_client *, char *)) {
    if(!web_client_can_access_dashboard(w))
        return web_client_permission_denied(w);

    return check_host_and_call(host, w, url, func);
}