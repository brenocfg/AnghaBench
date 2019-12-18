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
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct servent {int /*<<< orphan*/  s_port; } ;
struct hostent {char* h_name; int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addr; int /*<<< orphan*/  h_addrtype; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int WSAGetLastError () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  cleanup (int) ; 
 scalar_t__ connect (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct hostent* gethostbyname (char*) ; 
 struct servent* getservbyname (char*,char*) ; 
 int /*<<< orphan*/  getwhoisserver (int,char**) ; 
 char* host ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ optset ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int recv (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
	char ch;
	struct sockaddr_in sin;
	struct hostent *hp;
	struct servent *sp;
	SOCKET s;

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	getwhoisserver(argc, argv);
	argc -= optset;
	argv += optset;

    if (!host || !argc)
		usage();

	/* Start winsock */
	wVersionRequested = MAKEWORD( 1, 1 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		/* Tell the user that we couldn't find a usable */
		/* WinSock DLL.                                 */
		perror("whois: WSAStartup failed");
		cleanup(1);
	}

	hp = gethostbyname(host);
	if (hp == NULL) {
		(void)fprintf(stderr, "whois: %s: ", host);
		cleanup(1);
	}
	host = hp->h_name;

	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		perror("whois: socket");
		cleanup(1);
	}

	memset(/*(caddr_t)*/&sin, 0, sizeof(sin));
	sin.sin_family = hp->h_addrtype;
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("whois: bind");
		cleanup(1);
	}

	memcpy((char *)&sin.sin_addr, hp->h_addr, hp->h_length);
	sp = getservbyname("nicname", "tcp");
	if (sp == NULL) {
		(void)fprintf(stderr, "whois: nicname/tcp: unknown service\n");
		cleanup(1);
	}

	sin.sin_port = sp->s_port;

	/* have network connection; identify the host connected with */
	(void)printf("[%s]\n", hp->h_name);

	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		fprintf(stderr, "whois: connect error = %d\n", WSAGetLastError());
		cleanup(1);
	}

	/* WinSock doesn't allow using a socket as a file descriptor. */
	/* Have to use send() and recv().  whois will drop connection. */

	/* For each request */
	while (argc-- > 1)
	{
		/* Send the request */
		send(s, *argv, strlen(*argv), 0);
		send(s, " ", 1, 0);
		argv++;
	}
	/* Send the last request */
	send(s, *argv, strlen(*argv), 0);
	send(s, "\r\n", 2, 0);

	/* Receive anything and print it */
	while (recv(s, &ch, 1, 0) == 1)
		putchar(ch);

	cleanup(0);
	return 0;
}