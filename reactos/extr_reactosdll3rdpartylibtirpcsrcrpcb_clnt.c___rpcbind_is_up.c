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
typedef  int /*<<< orphan*/  sun ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct netconfig {int /*<<< orphan*/ * nc_protofmly; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  NC_LOOPBACK ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _PATH_RPCBINDSOCK ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ connect (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  endnetconfig (void*) ; 
 struct netconfig* getnetconfig (void*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 void* setnetconfig () ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

bool_t
__rpcbind_is_up()
{
	struct netconfig *nconf;
	struct sockaddr_un sun;
	void *localhandle;
	SOCKET sock;

	nconf = NULL;
	localhandle = setnetconfig();
	while ((nconf = getnetconfig(localhandle)) != NULL) {
		if (nconf->nc_protofmly != NULL &&
		    strcmp(nconf->nc_protofmly, NC_LOOPBACK) == 0)
			 break;
	}
	if (nconf == NULL)
		return (FALSE);

	endnetconfig(localhandle);

	memset(&sun, 0, sizeof sun);
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		return (FALSE);
	sun.sun_family = AF_UNIX;
	strncpy(sun.sun_path, _PATH_RPCBINDSOCK, sizeof(sun.sun_path));

	if (connect(sock, (struct sockaddr *)&sun, sizeof(sun)) == SOCKET_ERROR) {
		closesocket(sock);
		return (FALSE);
	}

	closesocket(sock);
	return (TRUE);
}