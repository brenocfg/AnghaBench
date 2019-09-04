#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  read_buff; scalar_t__ send_len; int /*<<< orphan*/  send_buff; } ;
typedef  TYPE_1__ libqnxr_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

int qnxr_cleanup (libqnxr_t *g) {
	if (!g) return -1;
	free (g->send_buff);
	g->send_len = 0;
	free (g->read_buff);
	return 0;
}