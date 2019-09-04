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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  php_socket ;

/* Variables and functions */
 int /*<<< orphan*/  UNBLOCK_SOURCE ; 
 int _php_mcast_source_op (int /*<<< orphan*/ *,int,struct sockaddr*,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

int php_mcast_unblock_source(
	php_socket *sock,
	int level,
	struct sockaddr *group,
	socklen_t group_len,
	struct sockaddr *source,
	socklen_t source_len,
	unsigned int if_index)
{
	return _php_mcast_source_op(sock, level, group, group_len, source, source_len, if_index, UNBLOCK_SOURCE);
}