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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  address ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int FAILURE ; 
 int SUCCESS ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phpdbg_remote_close (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phpdbg_rlog (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  phpdbg_set_async_io (int) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int phpdbg_remote_init(const char* address, unsigned short port, int server, int *socket, FILE **stream) {
	phpdbg_remote_close(*socket, *stream);

	if (server < 0) {
		phpdbg_rlog(fileno(stderr), "Initializing connection on %s:%u failed", address, port);

		return FAILURE;
	}

	phpdbg_rlog(fileno(stderr), "accepting connections on %s:%u", address, port);
	{
		struct sockaddr_storage address;
		socklen_t size = sizeof(address);
		char buffer[20] = {0};
		/* XXX error checks */
		memset(&address, 0, size);
		*socket = accept(server, (struct sockaddr *) &address, &size);
		inet_ntop(AF_INET, &(((struct sockaddr_in *)&address)->sin_addr), buffer, sizeof(buffer));

		phpdbg_rlog(fileno(stderr), "connection established from %s", buffer);
	}

#ifndef _WIN32
	dup2(*socket, fileno(stdout));
	dup2(*socket, fileno(stdin));

	setbuf(stdout, NULL);

	*stream = fdopen(*socket, "r+");

	phpdbg_set_async_io(*socket);
#endif
	return SUCCESS;
}