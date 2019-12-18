#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
struct TYPE_7__ {TYPE_1__ sock; } ;

/* Variables and functions */
 TYPE_2__* ctx ; 
 int /*<<< orphan*/  eloop_register_read_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,void (*) (void*,void*),TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubus_receive ; 
 scalar_t__ ubus_reconnect (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ubus_reconnect_timeout(void *eloop_data, void *user_ctx)
{
	if (ubus_reconnect(ctx, NULL)) {
		eloop_register_timeout(1, 0, ubus_reconnect_timeout, ctx, NULL);
		return;
	}

	eloop_register_read_sock(ctx->sock.fd, ubus_receive, ctx, NULL);
}