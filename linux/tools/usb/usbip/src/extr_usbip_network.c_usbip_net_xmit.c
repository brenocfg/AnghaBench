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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WAITALL ; 
 scalar_t__ recv (int,void*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ send (int,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t usbip_net_xmit(int sockfd, void *buff, size_t bufflen,
			      int sending)
{
	ssize_t nbytes;
	ssize_t total = 0;

	if (!bufflen)
		return 0;

	do {
		if (sending)
			nbytes = send(sockfd, buff, bufflen, 0);
		else
			nbytes = recv(sockfd, buff, bufflen, MSG_WAITALL);

		if (nbytes <= 0)
			return -1;

		buff	 = (void *)((intptr_t) buff + nbytes);
		bufflen	-= nbytes;
		total	+= nbytes;

	} while (bufflen > 0);

	return total;
}