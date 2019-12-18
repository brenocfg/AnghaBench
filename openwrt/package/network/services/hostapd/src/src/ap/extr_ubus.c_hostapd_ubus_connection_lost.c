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
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
struct ubus_context {TYPE_1__ sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ubus_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubus_reconnect_timeout ; 

__attribute__((used)) static void hostapd_ubus_connection_lost(struct ubus_context *ctx)
{
	eloop_unregister_read_sock(ctx->sock.fd);
	eloop_register_timeout(1, 0, ubus_reconnect_timeout, ctx, NULL);
}