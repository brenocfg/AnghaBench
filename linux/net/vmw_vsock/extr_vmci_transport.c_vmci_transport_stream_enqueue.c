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
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  qpair; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmci_qpair_enquev (int /*<<< orphan*/ ,struct msghdr*,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* vmci_trans (struct vsock_sock*) ; 

__attribute__((used)) static ssize_t vmci_transport_stream_enqueue(
	struct vsock_sock *vsk,
	struct msghdr *msg,
	size_t len)
{
	return vmci_qpair_enquev(vmci_trans(vsk)->qpair, msg, len, 0);
}