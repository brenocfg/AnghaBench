#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_un {scalar_t__ sun_path; } ;
struct sockaddr {int dummy; } ;
struct in_addr {scalar_t__ s_addr; } ;
struct hostent {scalar_t__ h_addrtype; scalar_t__* h_addr_list; } ;
typedef  int socklen_t ;
struct TYPE_10__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_9__ {scalar_t__ s_addr; } ;
struct TYPE_14__ {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; scalar_t__ sin_family; } ;
struct TYPE_13__ {TYPE_2__ sa; TYPE_6__ sa_unix; TYPE_6__ sa_inet; } ;
typedef  TYPE_5__ sa_t ;
struct TYPE_12__ {scalar_t__ sa_family; } ;
struct TYPE_11__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_15__ {TYPE_4__ sa; TYPE_3__ sa_inet; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  FCGI_ERROR ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ INADDR_NONE ; 
 scalar_t__ MAXFQDNLEN ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 TYPE_7__* allowed_clients ; 
 short atoi (char const*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  chmod (char const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fcgi_init () ; 
 int /*<<< orphan*/  fcgi_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fcgi_setup_signals () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (short) ; 
 scalar_t__ inet_addr (char*) ; 
 scalar_t__ inet_pton (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int is_fastcgi ; 
 int /*<<< orphan*/  is_initialized ; 
 scalar_t__ is_port_number (char const*) ; 
 scalar_t__ listen (int,int) ; 
 TYPE_7__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 struct hostent* php_network_gethostbyname (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

int fcgi_listen(const char *path, int backlog)
{
	char     *s;
	int       tcp = 0;
	char      host[MAXPATHLEN];
	short     port = 0;
	int       listen_socket;
	sa_t      sa;
	socklen_t sock_len;
#ifdef SO_REUSEADDR
# ifdef _WIN32
	BOOL reuse = 1;
# else
	int reuse = 1;
# endif
#endif

	if ((s = strchr(path, ':'))) {
		port = atoi(s+1);
		if (port != 0 && (s-path) < MAXPATHLEN) {
			strncpy(host, path, s-path);
			host[s-path] = '\0';
			tcp = 1;
		}
	} else if (is_port_number(path)) {
		port = atoi(path);
		if (port != 0) {
			host[0] = '\0';
			tcp = 1;
		}
	}

	/* Prepare socket address */
	if (tcp) {
		memset(&sa.sa_inet, 0, sizeof(sa.sa_inet));
		sa.sa_inet.sin_family = AF_INET;
		sa.sa_inet.sin_port = htons(port);
		sock_len = sizeof(sa.sa_inet);

		if (!*host || !strncmp(host, "*", sizeof("*")-1)) {
			sa.sa_inet.sin_addr.s_addr = htonl(INADDR_ANY);
		} else {
			sa.sa_inet.sin_addr.s_addr = inet_addr(host);
			if (sa.sa_inet.sin_addr.s_addr == INADDR_NONE) {
				struct hostent *hep;

				if(strlen(host) > MAXFQDNLEN) {
					hep = NULL;
				} else {
					hep = php_network_gethostbyname(host);
				}
				if (!hep || hep->h_addrtype != AF_INET || !hep->h_addr_list[0]) {
					fcgi_log(FCGI_ERROR, "Cannot resolve host name '%s'!\n", host);
					return -1;
				} else if (hep->h_addr_list[1]) {
					fcgi_log(FCGI_ERROR, "Host '%s' has multiple addresses. You must choose one explicitly!\n", host);
					return -1;
				}
				sa.sa_inet.sin_addr.s_addr = ((struct in_addr*)hep->h_addr_list[0])->s_addr;
			}
		}
	} else {
#ifdef _WIN32
		SECURITY_DESCRIPTOR  sd;
		SECURITY_ATTRIBUTES  saw;
		PACL                 acl;
		HANDLE namedPipe;

		memset(&sa, 0, sizeof(saw));
		saw.nLength = sizeof(saw);
		saw.bInheritHandle = FALSE;
		acl = prepare_named_pipe_acl(&sd, &saw);

		namedPipe = CreateNamedPipe(path,
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
			PIPE_TYPE_BYTE | PIPE_WAIT | PIPE_READMODE_BYTE,
			PIPE_UNLIMITED_INSTANCES,
			8192, 8192, 0, &saw);
		if (namedPipe == INVALID_HANDLE_VALUE) {
			return -1;
		}
		listen_socket = _open_osfhandle((intptr_t)namedPipe, 0);
		if (!is_initialized) {
			fcgi_init();
		}
		is_fastcgi = 1;
		return listen_socket;

#else
		size_t path_len = strlen(path);

		if (path_len >= sizeof(sa.sa_unix.sun_path)) {
			fcgi_log(FCGI_ERROR, "Listening socket's path name is too long.\n");
			return -1;
		}

		memset(&sa.sa_unix, 0, sizeof(sa.sa_unix));
		sa.sa_unix.sun_family = AF_UNIX;
		memcpy(sa.sa_unix.sun_path, path, path_len + 1);
		sock_len = (size_t)(((struct sockaddr_un *)0)->sun_path)	+ path_len;
#ifdef HAVE_SOCKADDR_UN_SUN_LEN
		sa.sa_unix.sun_len = sock_len;
#endif
		unlink(path);
#endif
	}

	/* Create, bind socket and start listen on it */
	if ((listen_socket = socket(sa.sa.sa_family, SOCK_STREAM, 0)) < 0 ||
#ifdef SO_REUSEADDR
	    setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) < 0 ||
#endif
	    bind(listen_socket, (struct sockaddr *) &sa, sock_len) < 0 ||
	    listen(listen_socket, backlog) < 0) {
		close(listen_socket);
		fcgi_log(FCGI_ERROR, "Cannot bind/listen socket - [%d] %s.\n",errno, strerror(errno));
		return -1;
	}

	if (!tcp) {
		chmod(path, 0777);
	} else {
		char *ip = getenv("FCGI_WEB_SERVER_ADDRS");
		char *cur, *end;
		int n;

		if (ip) {
			ip = strdup(ip);
			cur = ip;
			n = 0;
			while (*cur) {
				if (*cur == ',') n++;
				cur++;
			}
			allowed_clients = malloc(sizeof(sa_t) * (n+2));
			n = 0;
			cur = ip;
			while (cur) {
				end = strchr(cur, ',');
				if (end) {
					*end = 0;
					end++;
				}
				if (inet_pton(AF_INET, cur, &allowed_clients[n].sa_inet.sin_addr)>0) {
					allowed_clients[n].sa.sa_family = AF_INET;
					n++;
#ifdef HAVE_IPV6
				} else if (inet_pton(AF_INET6, cur, &allowed_clients[n].sa_inet6.sin6_addr)>0) {
					allowed_clients[n].sa.sa_family = AF_INET6;
					n++;
#endif
				} else {
					fcgi_log(FCGI_ERROR, "Wrong IP address '%s' in listen.allowed_clients", cur);
				}
				cur = end;
			}
			allowed_clients[n].sa.sa_family = 0;
			free(ip);
			if (!n) {
				fcgi_log(FCGI_ERROR, "There are no allowed addresses");
				/* don't clear allowed_clients as it will create an "open for all" security issue */
			}
		}
	}

	if (!is_initialized) {
		fcgi_init();
	}
	is_fastcgi = 1;

#ifdef _WIN32
	if (tcp) {
		listen_socket = _open_osfhandle((intptr_t)listen_socket, 0);
	}
#else
	fcgi_setup_signals();
#endif
	return listen_socket;
}