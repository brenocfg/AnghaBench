#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_1__* ops; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {scalar_t__ ss_family; } ;
struct TCP_Server_Info {TYPE_2__ srcaddr; struct socket* ssocket; } ;
struct TYPE_4__ {int (* bind ) (struct socket*,struct sockaddr*,int) ;} ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_server_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct socket*,struct sockaddr*,int) ; 

__attribute__((used)) static int
bind_socket(struct TCP_Server_Info *server)
{
	int rc = 0;
	if (server->srcaddr.ss_family != AF_UNSPEC) {
		/* Bind to the specified local IP address */
		struct socket *socket = server->ssocket;
		rc = socket->ops->bind(socket,
				       (struct sockaddr *) &server->srcaddr,
				       sizeof(server->srcaddr));
		if (rc < 0) {
			struct sockaddr_in *saddr4;
			struct sockaddr_in6 *saddr6;
			saddr4 = (struct sockaddr_in *)&server->srcaddr;
			saddr6 = (struct sockaddr_in6 *)&server->srcaddr;
			if (saddr6->sin6_family == AF_INET6)
				cifs_server_dbg(VFS, "Failed to bind to: %pI6c, error: %d\n",
					 &saddr6->sin6_addr, rc);
			else
				cifs_server_dbg(VFS, "Failed to bind to: %pI4, error: %d\n",
					 &saddr4->sin_addr.s_addr, rc);
		}
	}
	return rc;
}