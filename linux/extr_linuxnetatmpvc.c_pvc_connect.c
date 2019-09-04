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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int pvc_bind (struct socket*,struct sockaddr*,int) ; 

__attribute__((used)) static int pvc_connect(struct socket *sock, struct sockaddr *sockaddr,
		       int sockaddr_len, int flags)
{
	return pvc_bind(sock, sockaddr, sockaddr_len);
}