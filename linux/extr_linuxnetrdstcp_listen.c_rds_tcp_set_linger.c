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
struct linger {int l_onoff; int /*<<< orphan*/  l_linger; } ;
typedef  int /*<<< orphan*/  no_linger ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int /*<<< orphan*/  kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

void rds_tcp_set_linger(struct socket *sock)
{
	struct linger no_linger = {
		.l_onoff = 1,
		.l_linger = 0,
	};

	kernel_setsockopt(sock, SOL_SOCKET, SO_LINGER,
			  (char *)&no_linger, sizeof(no_linger));
}