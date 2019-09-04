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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
typedef  int /*<<< orphan*/  sbuf ;
typedef  int /*<<< orphan*/  hbuf ;

/* Variables and functions */
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t const,char*,char*,char*) ; 

__attribute__((used)) static void addrinfo_to_text(struct addrinfo *ai, char buf[],
			     const size_t buf_size)
{
	char hbuf[NI_MAXHOST];
	char sbuf[NI_MAXSERV];
	int rc;

	buf[0] = '\0';

	rc = getnameinfo(ai->ai_addr, ai->ai_addrlen, hbuf, sizeof(hbuf),
			 sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);
	if (rc)
		err("getnameinfo: %s", gai_strerror(rc));

	snprintf(buf, buf_size, "%s:%s", hbuf, sbuf);
}