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
struct socket {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int MSG_DONTWAIT ; 
 int MSG_EOR ; 
 int MSG_MORE ; 
 int MSG_NOSIGNAL ; 
 int kernel_sendpage (struct socket*,struct page*,int,size_t,int) ; 

__attribute__((used)) static int __ceph_tcp_sendpage(struct socket *sock, struct page *page,
		     int offset, size_t size, bool more)
{
	int flags = MSG_DONTWAIT | MSG_NOSIGNAL | (more ? MSG_MORE : MSG_EOR);
	int ret;

	ret = kernel_sendpage(sock, page, offset, size, flags);
	if (ret == -EAGAIN)
		ret = 0;

	return ret;
}