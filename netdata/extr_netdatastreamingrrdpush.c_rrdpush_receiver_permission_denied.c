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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct web_client {TYPE_1__ response; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ ,char*) ; 

int rrdpush_receiver_permission_denied(struct web_client *w) {
    // we always respond with the same message and error code
    // to prevent an attacker from gaining info about the error
    buffer_flush(w->response.data);
    buffer_sprintf(w->response.data, "You are not permitted to access this. Check the logs for more info.");
    return 401;
}