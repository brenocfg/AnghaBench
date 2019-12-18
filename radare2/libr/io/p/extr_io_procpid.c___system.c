#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* cb_printf ) (char*,int) ;} ;
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_6__ {int pid; } ;
typedef  TYPE_1__ RIOProcpid ;
typedef  TYPE_2__ RIODesc ;
typedef  TYPE_3__ RIO ;

/* Variables and functions */
 int atoi (char const*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 

__attribute__((used)) static char *__system(RIO *io, RIODesc *fd, const char *cmd) {
	RIOProcpid *iop = (RIOProcpid*)fd->data;
	if (!strncmp (cmd, "pid", 3)) {
		int pid = atoi (cmd + 3);
		if (pid > 0) {
			iop->pid = pid;
		}
		io->cb_printf ("%d\n", iop->pid);
	} else {
		eprintf ("Try: '=!pid'\n");
	}
	return NULL;
}