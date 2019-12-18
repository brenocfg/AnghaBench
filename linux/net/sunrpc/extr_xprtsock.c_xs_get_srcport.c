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
struct TYPE_2__ {scalar_t__ resvport; } ;
struct sock_xprt {int srcport; TYPE_1__ xprt; } ;

/* Variables and functions */
 int xs_get_random_port () ; 

__attribute__((used)) static int xs_get_srcport(struct sock_xprt *transport)
{
	int port = transport->srcport;

	if (port == 0 && transport->xprt.resvport)
		port = xs_get_random_port();
	return port;
}