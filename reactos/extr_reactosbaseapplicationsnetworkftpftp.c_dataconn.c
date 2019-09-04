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
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  from ;

/* Variables and functions */
 int WSAGetLastError () ; 
 int accept (int,struct sockaddr*,int*) ; 
 scalar_t__ closesocket (int) ; 
 int data ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ passivemode ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stdout ; 

int dataconn(const char *mode)
{
	struct sockaddr_in from;
	int s, fromlen = sizeof (from);

	if (passivemode)
		return (data);

	s = accept(data, (struct sockaddr *) &from, &fromlen);
	if (s < 0) {
		perror("ftp: accept");
		(void) closesocket(data), data = -1;
		return 0;
	}
	if(closesocket(data)) {
		int iret=WSAGetLastError ();
		fprintf(stdout,"Error closing socket(%d)\n",iret);
		(void) fflush(stdout);
	}

	data = s;
	return (data);
}