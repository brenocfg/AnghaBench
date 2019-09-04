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
 int MAX_SOCK_NAME_LEN ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  shutdown (int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int closesocket(int sockfd, char *name)
{
	char sockname[MAX_SOCK_NAME_LEN];

	if (sockfd)
		close(sockfd);
	sprintf(sockname, "/tmp/%s", name);
	unlink(sockname);
	shutdown(sockfd, 2);

	return 0;
}