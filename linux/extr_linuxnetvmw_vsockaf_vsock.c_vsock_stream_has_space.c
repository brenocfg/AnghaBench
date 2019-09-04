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
struct vsock_sock {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_2__ {int /*<<< orphan*/  (* stream_has_space ) (struct vsock_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vsock_sock*) ; 
 TYPE_1__* transport ; 

s64 vsock_stream_has_space(struct vsock_sock *vsk)
{
	return transport->stream_has_space(vsk);
}