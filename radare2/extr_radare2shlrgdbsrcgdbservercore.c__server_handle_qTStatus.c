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

/* Variables and functions */
 int send_ack (int /*<<< orphan*/ *) ; 
 int send_msg (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int _server_handle_qTStatus(libgdbr_t *g) {
	int ret;
	// TODO Handle proper reporting of trace status
	const char *message = "";
	if ((ret = send_ack (g)) < 0) {
		return -1;
	}
	return send_msg (g, message);
}