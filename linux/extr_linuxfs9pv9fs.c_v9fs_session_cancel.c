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
struct v9fs_session_info {int /*<<< orphan*/  clnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  p9_client_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct v9fs_session_info*) ; 

void v9fs_session_cancel(struct v9fs_session_info *v9ses) {
	p9_debug(P9_DEBUG_ERROR, "cancel session %p\n", v9ses);
	p9_client_disconnect(v9ses->clnt);
}