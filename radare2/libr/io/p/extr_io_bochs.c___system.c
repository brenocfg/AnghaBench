#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* cb_printf ) (char*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  TYPE_1__ RIO ;

/* Variables and functions */
 int /*<<< orphan*/  bochs_cmd_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  bochs_send_cmd (TYPE_2__*,char const*,int) ; 
 TYPE_2__* desc ; 
 int /*<<< orphan*/  lprintf (char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *__system(RIO *io, RIODesc *fd, const char *cmd) {
        lprintf ("system command (%s)\n", cmd);
        if (!strcmp (cmd, "help")) {
                lprintf ("Usage: =!cmd args\n"
                        " =!:<bochscmd>      - Send a bochs command.\n"
                        " =!dobreak          - pause bochs.\n");
		lprintf ("io_system: Enviando commando bochs\n");
		bochs_send_cmd (desc, &cmd[1], true);
		io->cb_printf ("%s\n", desc->data);
	} else if (!strncmp (cmd, "dobreak", 7)) {
		bochs_cmd_stop (desc);
		io->cb_printf ("%s\n", desc->data);
	}
        return NULL;
}