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
struct in_addr {unsigned long s_addr; } ;
struct hostent {char* h_name; char** h_addr_list; char* h_addr; int h_length; int /*<<< orphan*/  h_addrtype; scalar_t__ h_aliases; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int WSAGetLastError () ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 scalar_t__ connect (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct hostent* gethostbyname (char*) ; 
 struct servent* getservbyname (char*,char*) ; 
 unsigned long inet_addr (char*) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  isprint (char) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 char* rindex (char*,char) ; 
 int /*<<< orphan*/  send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 

void
netfinger(char *name)
{
	extern int lflag;
	char c, lastc;
	struct in_addr defaddr;
	struct hostent *hp, def;
	struct servent *sp;
	struct sockaddr_in sin;
	SOCKET s;
	char *alist[1], *host;

	/* If this is a local request */
	if (!(host = rindex(name, '@')))
		return;

	*host++ = '\0';
	if (isdigit(*host) && (defaddr.s_addr = inet_addr(host)) != (unsigned long)-1) {
		def.h_name = host;
		def.h_addr_list = alist;
		def.h_addr = (char *)&defaddr;
		def.h_length = sizeof(struct in_addr);
		def.h_addrtype = AF_INET;
		def.h_aliases = 0;
		hp = &def;
	} else if (!(hp = gethostbyname(host))) {
		(void)fprintf(stderr,
		    "finger: unknown host: %s\n", host);
		return;
	}
	if (!(sp = getservbyname("finger", "tcp"))) {
		(void)fprintf(stderr, "finger: tcp/finger: unknown service\n");
		return;
	}
	sin.sin_family = hp->h_addrtype;
	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
	sin.sin_port = sp->s_port;
	if ((s = socket(hp->h_addrtype, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		perror("finger: socket");
		return;
	}

	/* have network connection; identify the host connected with */
	(void)printf("[%s]\n", hp->h_name);
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		fprintf(stderr, "finger: connect rc = %d", WSAGetLastError());
		(void)closesocket(s);
		return;
	}

	/* -l flag for remote fingerd  */
	if (lflag)
		send(s, "/W ", 3, 0);
	/* send the name followed by <CR><LF> */
	send(s, name, strlen(name), 0);
	send(s, "\r\n", 2, 0);

	/*
	 * Read from the remote system; once we're connected, we assume some
	 * data.  If none arrives, we hang until the user interrupts.
	 *
	 * If we see a <CR> or a <CR> with the high bit set, treat it as
	 * a newline; if followed by a newline character, only output one
	 * newline.
	 *
	 * Otherwise, all high bits are stripped; if it isn't printable and
	 * it isn't a space, we can simply set the 7th bit.  Every ASCII
	 * character with bit 7 set is printable.
	 */
	lastc = 0;
	while (recv(s, &c, 1, 0) == 1) {
		c &= 0x7f;
		if (c == 0x0d) {
			if (lastc == '\r')	/* ^M^M - skip dupes */
				continue;
			c = '\n';
			lastc = '\r';
		} else {
			if (!isprint(c) && !isspace(c))
				c |= 0x40;
			if (lastc != '\r' || c != '\n')
				lastc = c;
			else {
				lastc = '\n';
				continue;
			}
		}
		putchar(c);
	}
	if (lastc != '\n')
		putchar('\n');
	putchar('\n');
	(void)closesocket(s);
}