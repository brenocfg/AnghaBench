#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ last_code; TYPE_1__* registers; scalar_t__ data; } ;
typedef  TYPE_2__ libgdbr_t ;
struct TYPE_12__ {int valid; } ;
struct TYPE_10__ {scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ MSG_OK ; 
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  gdbr_lock_enter (TYPE_2__*) ; 
 int /*<<< orphan*/  gdbr_lock_leave (TYPE_2__*) ; 
 int /*<<< orphan*/  gdbr_read_registers (TYPE_2__*) ; 
 int /*<<< orphan*/  gdbr_write_bin_registers (TYPE_2__*) ; 
 int /*<<< orphan*/  gdbr_write_register (TYPE_2__*,int,char*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 TYPE_3__ reg_cache ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

int gdbr_write_reg(libgdbr_t *g, const char *name, char *value, int len) {
	// static variable that keeps the information if writing
	// register through packet <P> was possible
	static int P = 1;
	int i = 0;
	int ret = -1;
	if (!g) {
		return -1;
	}

	if (!gdbr_lock_enter (g)) {
		goto end;
	}

	reg_cache.valid = false;
	while (g->registers[i].size > 0) {
		if (!strcmp (g->registers[i].name, name)) {
			break;
		}
		i++;
	}
	if (g->registers[i].size == 0) {
		eprintf ("Error registername <%s> not found in profile\n", name);
		ret = -1;
		goto end;
	}
	if (P) {
		gdbr_write_register (g, i, value, len);
		if (g->last_code == MSG_OK) {
			return 0;
		}
		P = 0;
	}
	gdbr_read_registers (g);
	memcpy (g->data + g->registers[i].offset, value, len);
	gdbr_write_bin_registers (g);

	ret = 0;
end:
	gdbr_lock_leave (g);
	return ret;
}