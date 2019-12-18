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
struct ubus_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubus_handle_event (struct ubus_context*) ; 

__attribute__((used)) static void ubus_receive(int sock, void *eloop_ctx, void *sock_ctx)
{
	struct ubus_context *ctx = eloop_ctx;
	ubus_handle_event(ctx);
}