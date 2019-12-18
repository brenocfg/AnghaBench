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
typedef  int /*<<< orphan*/  libgdbr_t ;
typedef  int /*<<< orphan*/  gdbr_server_cmd_cb ;

/* Variables and functions */
 scalar_t__ send_ack (int /*<<< orphan*/ *) ; 
 int send_msg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int _server_handle_qAttached(libgdbr_t *g, gdbr_server_cmd_cb cmd_cb, void *core_ptr) {
	if (send_ack (g) < 0) {
		return -1;
	}
	// TODO check if process was attached or created
	// Right now, says that process was created
	return send_msg (g, "0");
}