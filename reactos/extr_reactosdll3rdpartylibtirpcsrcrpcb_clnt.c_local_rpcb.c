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
typedef  int /*<<< orphan*/  u_int ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct netconfig {scalar_t__ nc_semantics; int /*<<< orphan*/  nc_netid; int /*<<< orphan*/  nc_protofmly; } ;
struct netbuf {int maxlen; struct sockaddr_un* buf; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;
typedef  int /*<<< orphan*/  mutex_t ;
struct TYPE_2__ {void* cf_stat; } ;
typedef  scalar_t__ SOCKET ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  CLNT_CONTROL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSET_FD_CLOSE ; 
 char* IN4_LOCALHOST_STRING ; 
 char* IN6_LOCALHOST_STRING ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  NC_INET ; 
 scalar_t__ NC_TPI_COTS ; 
 scalar_t__ NC_TPI_COTS_ORD ; 
 scalar_t__ RPCBPROG ; 
 scalar_t__ RPCBVERS ; 
 void* RPC_UNKNOWNPROTO ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SUN_LEN (struct sockaddr_un*) ; 
 int /*<<< orphan*/  _PATH_RPCBINDSOCK ; 
 size_t __rpc_get_t_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __rpc_nconf2fd (struct netconfig*) ; 
 int /*<<< orphan*/ * clnt_vc_create (scalar_t__,struct netbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  endnetconfig (void*) ; 
 int /*<<< orphan*/ * getclnthandle (char*,struct netconfig*,int /*<<< orphan*/ *) ; 
 struct netconfig* getnetconfig (void*) ; 
 struct netconfig* getnetconfigent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ rpc_createerr ; 
 void* setnetconfig () ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CLIENT *
local_rpcb()
{
	CLIENT *client;
	static struct netconfig *loopnconf;
	static char *hostname;
	extern mutex_t loopnconf_lock;
	SOCKET sock;
	size_t tsize;
	struct netbuf nbuf;
	struct sockaddr_un sun;

	/*
	 * Try connecting to the local rpcbind through a local socket
	 * first. If this doesn't work, try all transports defined in
	 * the netconfig file.
	 */
	memset(&sun, 0, sizeof sun);
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		goto try_nconf;
	sun.sun_family = AF_UNIX;
	strcpy(sun.sun_path, _PATH_RPCBINDSOCK);
	nbuf.len = SUN_LEN(&sun);
	nbuf.maxlen = sizeof (struct sockaddr_un);
	nbuf.buf = &sun;

	tsize = __rpc_get_t_size(AF_UNIX, 0, 0);
	client = clnt_vc_create(sock, &nbuf, (rpcprog_t)RPCBPROG,
	    (rpcvers_t)RPCBVERS, (u_int)tsize, (u_int)tsize, 
        NULL, NULL, NULL);

	if (client != NULL) {
		/* Mark the socket to be closed in destructor */
		(void) CLNT_CONTROL(client, CLSET_FD_CLOSE, NULL);
		return client;
	}

	/* Nobody needs this socket anymore; free the descriptor. */
	closesocket(sock);

try_nconf:

/* VARIABLES PROTECTED BY loopnconf_lock: loopnconf */
	mutex_lock(&loopnconf_lock);
	if (loopnconf == NULL) {
		struct netconfig *nconf, *tmpnconf = NULL;
		void *nc_handle;
		SOCKET fd;

		nc_handle = setnetconfig();
		if (nc_handle == NULL) {
			/* fails to open netconfig file */
			//syslog (LOG_ERR, "rpc: failed to open " NETCONFIG);
			rpc_createerr.cf_stat = RPC_UNKNOWNPROTO;
			mutex_unlock(&loopnconf_lock);
			return (NULL);
		}
		while ((nconf = getnetconfig(nc_handle)) != NULL) {
#ifdef INET6
			if ((strcmp(nconf->nc_protofmly, NC_INET6) == 0 ||
#else
			if ((
#endif
			     strcmp(nconf->nc_protofmly, NC_INET) == 0) &&
			    (nconf->nc_semantics == NC_TPI_COTS ||
			     nconf->nc_semantics == NC_TPI_COTS_ORD)) {
				fd = __rpc_nconf2fd(nconf);
				/*
				 * Can't create a socket, assume that
				 * this family isn't configured in the kernel.
				 */
				if (fd == SOCKET_ERROR)
					continue;
 				closesocket(fd);
				tmpnconf = nconf;
				if (!strcmp(nconf->nc_protofmly, NC_INET))
					hostname = IN4_LOCALHOST_STRING;
				else
					hostname = IN6_LOCALHOST_STRING;
			}
		}
		if (tmpnconf == NULL) {
 			rpc_createerr.cf_stat = RPC_UNKNOWNPROTO;
			mutex_unlock(&loopnconf_lock);
			return (NULL);
		}
		loopnconf = getnetconfigent(tmpnconf->nc_netid);
		/* loopnconf is never freed */
		endnetconfig(nc_handle);
	}
	mutex_unlock(&loopnconf_lock);
	client = getclnthandle(hostname, loopnconf, NULL);
	return (client);
}