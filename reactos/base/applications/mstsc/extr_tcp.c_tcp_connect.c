#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct hostent {int /*<<< orphan*/  h_addr; } ;
struct addrinfo {int ai_addrlen; struct addrinfo* ai_next; struct sockaddr* ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  option_value ;
struct TYPE_6__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  RD_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  INADDR_NONE ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int STREAM_COUNT ; 
 int /*<<< orphan*/  TCP_CLOSE (int) ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 char* TCP_STRERROR ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 TYPE_3__ g_in ; 
 TYPE_2__* g_out ; 
 int /*<<< orphan*/  g_reconnect_loop ; 
 int g_sock ; 
 scalar_t__ g_ssl_server ; 
 int g_tcp_port_rdp ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 struct hostent* gethostbyname (char*) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ xmalloc (int) ; 

RD_BOOL
tcp_connect(char *server)
{
	socklen_t option_len;
	uint32 option_value;
	int i;

#ifdef IPv6

	int n;
	struct addrinfo hints, *res, *ressave;
	char tcp_port_rdp_s[10];

	snprintf(tcp_port_rdp_s, 10, "%d", g_tcp_port_rdp);

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((n = getaddrinfo(server, tcp_port_rdp_s, &hints, &res)))
	{
		error("getaddrinfo: %s\n", gai_strerror(n));
		return False;
	}

	ressave = res;
	g_sock = -1;
	while (res)
	{
		g_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (!(g_sock < 0))
		{
			if (connect(g_sock, res->ai_addr, res->ai_addrlen) == 0)
				break;
			TCP_CLOSE(g_sock);
			g_sock = -1;
		}
		res = res->ai_next;
	}
	freeaddrinfo(ressave);

	if (g_sock == -1)
	{
		error("%s: unable to connect\n", server);
		return False;
	}

#else /* no IPv6 support */

	struct hostent *nslookup;
	struct sockaddr_in servaddr;

	if ((nslookup = gethostbyname(server)) != NULL)
	{
		memcpy(&servaddr.sin_addr, nslookup->h_addr, sizeof(servaddr.sin_addr));
	}
	else if ((servaddr.sin_addr.s_addr = inet_addr(server)) == INADDR_NONE)
	{
		error("%s: unable to resolve host\n", server);
		return False;
	}

	if ((g_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		error("socket: %s\n", TCP_STRERROR);
		return False;
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons((uint16) g_tcp_port_rdp);

	if (connect(g_sock, (struct sockaddr *) &servaddr, sizeof(struct sockaddr)) < 0)
	{
		if (!g_reconnect_loop)
			error("connect: %s\n", TCP_STRERROR);

		TCP_CLOSE(g_sock);
		g_sock = -1;
		return False;
	}

#endif /* IPv6 */

	option_value = 1;
	option_len = sizeof(option_value);
	setsockopt(g_sock, IPPROTO_TCP, TCP_NODELAY, (void *) &option_value, option_len);
	/* receive buffer must be a least 16 K */
	if (getsockopt(g_sock, SOL_SOCKET, SO_RCVBUF, (void *) &option_value, &option_len) == 0)
	{
		if (option_value < (1024 * 16))
		{
			option_value = 1024 * 16;
			option_len = sizeof(option_value);
			setsockopt(g_sock, SOL_SOCKET, SO_RCVBUF, (void *) &option_value,
				   option_len);
		}
	}

	g_in.size = 4096;
	g_in.data = (uint8 *) xmalloc(g_in.size);

	for (i = 0; i < STREAM_COUNT; i++)
	{
		g_out[i].size = 4096;
		g_out[i].data = (uint8 *) xmalloc(g_out[i].size);
	}

#ifdef WITH_SSL
	g_ssl_server = xmalloc(strlen(server)+1);
#endif /* WITH_SSL */

	return True;
}