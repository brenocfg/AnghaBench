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
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_FASTOPEN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int sendmsg_to_server (int /*<<< orphan*/ ,struct sockaddr_storage const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fastconnect_to_server(const struct sockaddr_storage *addr,
				 socklen_t addr_len)
{
	int sendmsg_err;

	return sendmsg_to_server(SOCK_STREAM, addr, addr_len, /*set_cmsg*/0,
				 MSG_FASTOPEN, &sendmsg_err);
}