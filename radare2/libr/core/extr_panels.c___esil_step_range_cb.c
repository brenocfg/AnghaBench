#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_6__ {scalar_t__ offset; int /*<<< orphan*/  num; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __esil_init (TYPE_1__*) ; 
 int /*<<< orphan*/  __esil_step_to (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_1__*,int,int) ; 
 char* __show_status_input (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ r_num_math (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (int /*<<< orphan*/ *) ; 

int __esil_step_range_cb(void *user) {
	RStrBuf *rsb = r_strbuf_new (NULL);
	RCore *core = (RCore *)user;
	r_strbuf_append (rsb, "start addr: ");
	char *s = __show_status_input (core, r_strbuf_get (rsb));
	r_strbuf_append (rsb, s);
	r_strbuf_append (rsb, " end addr: ");
	char *d = __show_status_input (core, r_strbuf_get (rsb));
	r_strbuf_free (rsb);
	ut64 s_a = r_num_math (core->num, s);
	ut64 d_a = r_num_math (core->num, d);
	if (s_a >= d_a) {
		return 0;
	}
	ut64 tmp = core->offset;
	core->offset = s_a;
	__esil_init (core);
	__esil_step_to (core, d_a);
	core->offset = tmp;
	__set_refresh_all ((RCore *)user, false, false);
	return 0;
}