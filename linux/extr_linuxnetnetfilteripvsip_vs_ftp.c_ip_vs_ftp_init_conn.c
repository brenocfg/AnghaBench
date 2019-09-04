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
struct ip_vs_conn {int /*<<< orphan*/  flags; } ;
struct ip_vs_app {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_CONN_F_NFCT ; 

__attribute__((used)) static int
ip_vs_ftp_init_conn(struct ip_vs_app *app, struct ip_vs_conn *cp)
{
	/* We use connection tracking for the command connection */
	cp->flags |= IP_VS_CONN_F_NFCT;
	return 0;
}