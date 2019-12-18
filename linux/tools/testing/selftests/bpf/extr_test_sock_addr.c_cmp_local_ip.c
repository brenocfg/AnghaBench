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
struct sockaddr_storage {int dummy; } ;

/* Variables and functions */
 int cmp_sock_addr (int /*<<< orphan*/ ,int,struct sockaddr_storage const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getsockname ; 

__attribute__((used)) static int cmp_local_ip(int sock1, const struct sockaddr_storage *addr2)
{
	return cmp_sock_addr(getsockname, sock1, addr2, /*cmp_port*/ 0);
}