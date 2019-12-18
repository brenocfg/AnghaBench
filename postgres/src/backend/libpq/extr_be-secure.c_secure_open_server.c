#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* peer_cn; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int be_tls_open_server (TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 

int
secure_open_server(Port *port)
{
	int			r = 0;

#ifdef USE_SSL
	r = be_tls_open_server(port);

	ereport(DEBUG2,
			(errmsg("SSL connection from \"%s\"",
					port->peer_cn ? port->peer_cn : "(anonymous)")));
#endif

	return r;
}