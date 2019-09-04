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
typedef  int /*<<< orphan*/  u8 ;
struct iucv_path {struct iucv_connection* private; } ;
struct iucv_connection {int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_EVENT_CONN_REJ ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iucv_connection*) ; 

__attribute__((used)) static void netiucv_callback_connrej(struct iucv_path *path, u8 *ipuser)
{
	struct iucv_connection *conn = path->private;

	fsm_event(conn->fsm, CONN_EVENT_CONN_REJ, conn);
}