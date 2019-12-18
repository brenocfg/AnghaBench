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
struct TYPE_3__ {int /*<<< orphan*/  gdbr_lock; int /*<<< orphan*/  read_buff; int /*<<< orphan*/  send_buff; scalar_t__ send_len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ libgdbr_t ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_th_lock_free (int /*<<< orphan*/ ) ; 

int gdbr_cleanup(libgdbr_t *g) {
	if (!g) {
		return -1;
	}
	R_FREE (g->data);
	g->send_len = 0;
	R_FREE (g->send_buff);
	R_FREE (g->read_buff);
	r_th_lock_free (g->gdbr_lock);
	return 0;
}