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
typedef  int /*<<< orphan*/  zval ;
struct sockaddr {int dummy; } ;
struct msghdr {int /*<<< orphan*/  msg_namelen; struct sockaddr* msg_name; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  ser_context ;

/* Variables and functions */
 int /*<<< orphan*/  from_zval_write_sockaddr_aux (int /*<<< orphan*/  const*,struct sockaddr**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void from_zval_write_name(const zval *zname_arr, char *msghdr_c, ser_context *ctx)
{
	struct sockaddr	*sockaddr;
	socklen_t		sockaddr_len;
	struct msghdr	*msghdr = (struct msghdr *)msghdr_c;

	from_zval_write_sockaddr_aux(zname_arr, &sockaddr, &sockaddr_len, ctx);

	msghdr->msg_name = sockaddr;
	msghdr->msg_namelen = sockaddr_len;
}