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
struct sockaddr {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  INIT () ; 
 int MSG_FASTOPEN ; 
 int /*<<< orphan*/  PFUNC () ; 
 int /*<<< orphan*/  connect (int,struct sockaddr const*,scalar_t__) ; 
 scalar_t__ errno ; 
 int true_sendto (int,void const*,size_t,int,struct sockaddr const*,scalar_t__) ; 

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
	       const struct sockaddr *dest_addr, socklen_t addrlen) {
	INIT();
	PFUNC();
	if (flags & MSG_FASTOPEN) {
		if (!connect(sockfd, dest_addr, addrlen) && errno != EINPROGRESS) {
			return -1;
		}
		dest_addr = NULL;
		addrlen = 0;
		flags &= ~MSG_FASTOPEN;
	}
	return true_sendto(sockfd, buf, len, flags, dest_addr, addrlen);
}