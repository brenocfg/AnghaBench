#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ offset; } ;
struct TYPE_3__ {scalar_t__ copied; scalar_t__ len; scalar_t__ offset; } ;
struct sock_xprt {TYPE_2__ xmit; TYPE_1__ recv; } ;

/* Variables and functions */

__attribute__((used)) static void
xs_stream_reset_connect(struct sock_xprt *transport)
{
	transport->recv.offset = 0;
	transport->recv.len = 0;
	transport->recv.copied = 0;
	transport->xmit.offset = 0;
}