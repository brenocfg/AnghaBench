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
typedef  int /*<<< orphan*/  user_timeout ;
struct socket {int dummy; } ;

/* Variables and functions */
 int O2NET_TCP_USER_TIMEOUT ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  TCP_USER_TIMEOUT ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int o2net_set_usertimeout(struct socket *sock)
{
	int user_timeout = O2NET_TCP_USER_TIMEOUT;

	return kernel_setsockopt(sock, SOL_TCP, TCP_USER_TIMEOUT,
				(void *)&user_timeout, sizeof(user_timeout));
}