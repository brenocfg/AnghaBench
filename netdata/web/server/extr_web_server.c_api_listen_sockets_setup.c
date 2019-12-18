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

/* Variables and functions */
 int D_WEB_CLIENT ; 
 int /*<<< orphan*/  api_sockets ; 
 int debug_flags ; 
 int /*<<< orphan*/  debug_sockets () ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int listen_sockets_setup (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void api_listen_sockets_setup(void) {
	int socks = listen_sockets_setup(&api_sockets);

	if(!socks)
		fatal("LISTENER: Cannot listen on any API socket. Exiting...");

	if(unlikely(debug_flags & D_WEB_CLIENT))
		debug_sockets();

	return;
}