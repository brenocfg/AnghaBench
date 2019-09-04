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
struct ip_vs_conn {struct ip_vs_app* app; } ;
struct ip_vs_app {int /*<<< orphan*/  (* done_conn ) (struct ip_vs_app*,struct ip_vs_conn*) ;int /*<<< orphan*/  (* unbind_conn ) (struct ip_vs_app*,struct ip_vs_conn*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_app_inc_put (struct ip_vs_app*) ; 
 int /*<<< orphan*/  stub1 (struct ip_vs_app*,struct ip_vs_conn*) ; 
 int /*<<< orphan*/  stub2 (struct ip_vs_app*,struct ip_vs_conn*) ; 

void ip_vs_unbind_app(struct ip_vs_conn *cp)
{
	struct ip_vs_app *inc = cp->app;

	if (!inc)
		return;

	if (inc->unbind_conn)
		inc->unbind_conn(inc, cp);
	if (inc->done_conn)
		inc->done_conn(inc, cp);
	ip_vs_app_inc_put(inc);
	cp->app = NULL;
}