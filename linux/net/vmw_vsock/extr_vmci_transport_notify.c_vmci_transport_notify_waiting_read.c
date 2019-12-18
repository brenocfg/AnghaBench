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
struct TYPE_2__ {int /*<<< orphan*/  qpair; } ;

/* Variables and functions */
 int /*<<< orphan*/  PKT_FIELD (struct vsock_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peer_waiting_read ; 
 scalar_t__ vmci_qpair_produce_buf_ready (int /*<<< orphan*/ ) ; 
 TYPE_1__* vmci_trans (struct vsock_sock*) ; 

__attribute__((used)) static bool vmci_transport_notify_waiting_read(struct vsock_sock *vsk)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	if (!PKT_FIELD(vsk, peer_waiting_read))
		return false;

	/* For now we ignore the wait information and just see if there is any
	 * data for our peer to read.  Note that improving this function to be
	 * more intelligent will not require a protocol change and will retain
	 * compatibility between endpoints with mixed versions of this
	 * function.
	 */
	return vmci_qpair_produce_buf_ready(vmci_trans(vsk)->qpair) > 0;
#else
	return true;
#endif
}