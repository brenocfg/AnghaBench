#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort ;
struct socket {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  cl ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EADDRINUSE ; 
 int EINVAL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int kernel_bind (struct socket*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int p9_ipport_resv_max ; 
 int p9_ipport_resv_min ; 

__attribute__((used)) static int p9_bind_privport(struct socket *sock)
{
	struct sockaddr_in cl;
	int port, err = -EINVAL;

	memset(&cl, 0, sizeof(cl));
	cl.sin_family = AF_INET;
	cl.sin_addr.s_addr = INADDR_ANY;
	for (port = p9_ipport_resv_max; port >= p9_ipport_resv_min; port--) {
		cl.sin_port = htons((ushort)port);
		err = kernel_bind(sock, (struct sockaddr *)&cl, sizeof(cl));
		if (err != -EADDRINUSE)
			break;
	}
	return err;
}