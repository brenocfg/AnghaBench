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
struct sock_xprt {int dummy; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 

__attribute__((used)) static ssize_t
xs_read_stream_call(struct sock_xprt *transport, struct msghdr *msg, int flags)
{
	return -ESHUTDOWN;
}