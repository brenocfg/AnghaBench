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
struct svc_xprt {int dummy; } ;
struct svc_serv {int dummy; } ;
struct sockaddr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 struct svc_xprt* svc_create_socket (struct svc_serv*,int /*<<< orphan*/ ,struct net*,struct sockaddr*,int,int) ; 

__attribute__((used)) static struct svc_xprt *svc_tcp_create(struct svc_serv *serv,
				       struct net *net,
				       struct sockaddr *sa, int salen,
				       int flags)
{
	return svc_create_socket(serv, IPPROTO_TCP, net, sa, salen, flags);
}