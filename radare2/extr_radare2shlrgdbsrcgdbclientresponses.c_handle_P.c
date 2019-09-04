#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ data_len; int /*<<< orphan*/  last_code; } ;
typedef  TYPE_1__ libgdbr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOT_SUPPORTED ; 
 int /*<<< orphan*/  MSG_OK ; 
 int send_ack (TYPE_1__*) ; 

int handle_P(libgdbr_t *g) {
	if (g->data_len == 0) {
		g->last_code = MSG_NOT_SUPPORTED;
	} else {
		g->last_code = MSG_OK;
	}
	return send_ack (g);
}