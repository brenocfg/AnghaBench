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
struct sock {int dummy; } ;
struct TYPE_2__ {int (* shutdown ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* transport ; 
 int /*<<< orphan*/  vsock_sk (struct sock*) ; 

__attribute__((used)) static int vsock_send_shutdown(struct sock *sk, int mode)
{
	return transport->shutdown(vsock_sk(sk), mode);
}