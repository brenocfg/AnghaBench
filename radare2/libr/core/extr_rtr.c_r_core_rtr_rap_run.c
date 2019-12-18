#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* context; } ;
struct TYPE_7__ {int /*<<< orphan*/  io; } ;
struct TYPE_6__ {int breaked; } ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int R_PERM_RW ; 
 TYPE_5__* r_cons_singleton () ; 
 int /*<<< orphan*/  r_core_serve (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_io_desc_close (int /*<<< orphan*/ *) ; 
 scalar_t__ r_io_is_listener (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_io_open_nomap (int /*<<< orphan*/ ,char*,int,int) ; 
 char* r_str_newf (char*,char const*) ; 

__attribute__((used)) static bool r_core_rtr_rap_run(RCore *core, const char *input) {
	char *file = r_str_newf ("rap://%s", input);
	int flags = R_PERM_RW;
	RIODesc *fd = r_io_open_nomap (core->io, file, flags, 0644);
	if (fd) {
		if (r_io_is_listener (core->io)) {
			if (!r_core_serve (core, fd)) {
				r_cons_singleton ()->context->breaked = true;
			}
			r_io_desc_close (fd);
			// avoid double free, we are not the owners of this fd so we can't destroy it
			//r_io_desc_free (fd);
		}
	} else {
		r_cons_singleton ()->context->breaked = true;
	}
	return !r_cons_singleton ()->context->breaked;
	// r_core_cmdf (core, "o rap://%s", input);
}