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
struct ip_vs_protocol {int (* app_conn_bind ) (struct ip_vs_conn*) ;} ;
struct ip_vs_conn {int dummy; } ;

/* Variables and functions */
 int stub1 (struct ip_vs_conn*) ; 

int ip_vs_bind_app(struct ip_vs_conn *cp,
		   struct ip_vs_protocol *pp)
{
	return pp->app_conn_bind(cp);
}