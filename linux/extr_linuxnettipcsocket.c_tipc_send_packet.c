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
struct msghdr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 size_t TIPC_MAX_USER_MSG_SIZE ; 
 int tipc_sendstream (struct socket*,struct msghdr*,size_t) ; 

__attribute__((used)) static int tipc_send_packet(struct socket *sock, struct msghdr *m, size_t dsz)
{
	if (dsz > TIPC_MAX_USER_MSG_SIZE)
		return -EMSGSIZE;

	return tipc_sendstream(sock, m, dsz);
}