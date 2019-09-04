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
typedef  int /*<<< orphan*/  keepidle ;
typedef  int /*<<< orphan*/  keepcnt ;
typedef  int /*<<< orphan*/  keepalive ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  TCP_KEEPCNT ; 
 int /*<<< orphan*/  TCP_KEEPIDLE ; 
 int /*<<< orphan*/  TCP_KEEPINTVL ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int rds_tcp_keepalive(struct socket *sock)
{
	/* values below based on xs_udp_default_timeout */
	int keepidle = 5; /* send a probe 'keepidle' secs after last data */
	int keepcnt = 5; /* number of unack'ed probes before declaring dead */
	int keepalive = 1;
	int ret = 0;

	ret = kernel_setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE,
				(char *)&keepalive, sizeof(keepalive));
	if (ret < 0)
		goto bail;

	ret = kernel_setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT,
				(char *)&keepcnt, sizeof(keepcnt));
	if (ret < 0)
		goto bail;

	ret = kernel_setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE,
				(char *)&keepidle, sizeof(keepidle));
	if (ret < 0)
		goto bail;

	/* KEEPINTVL is the interval between successive probes. We follow
	 * the model in xs_tcp_finish_connecting() and re-use keepidle.
	 */
	ret = kernel_setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL,
				(char *)&keepidle, sizeof(keepidle));
bail:
	return ret;
}