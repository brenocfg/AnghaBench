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
typedef  int /*<<< orphan*/  u32 ;
struct vsock_sock {TYPE_1__* owner; scalar_t__ trusted; } ;
struct TYPE_2__ {int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 scalar_t__ vmci_is_context_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vmci_transport_is_trusted(struct vsock_sock *vsock, u32 peer_cid)
{
	return vsock->trusted ||
	       vmci_is_context_owner(peer_cid, vsock->owner->uid);
}