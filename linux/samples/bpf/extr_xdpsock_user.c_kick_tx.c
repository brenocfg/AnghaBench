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
struct xsk_socket_info {int /*<<< orphan*/  xsk; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EBUSY ; 
 scalar_t__ ENOBUFS ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit_with_error (scalar_t__) ; 
 int sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_socket__fd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kick_tx(struct xsk_socket_info *xsk)
{
	int ret;

	ret = sendto(xsk_socket__fd(xsk->xsk), NULL, 0, MSG_DONTWAIT, NULL, 0);
	if (ret >= 0 || errno == ENOBUFS || errno == EAGAIN || errno == EBUSY)
		return;
	exit_with_error(errno);
}