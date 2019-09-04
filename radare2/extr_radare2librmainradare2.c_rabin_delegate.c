#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* file; int /*<<< orphan*/  io; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  user; } ;
struct TYPE_8__ {int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  RThreadFunctionRet ;
typedef  TYPE_2__ RThread ;
typedef  TYPE_3__ RIODesc ;

/* Variables and functions */
 int /*<<< orphan*/  R_TH_STOP ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_6__ r ; 
 int /*<<< orphan*/  r_core_cmd (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ r_file_exists (int /*<<< orphan*/ ) ; 
 TYPE_3__* r_io_desc_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* r_sys_cmd_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_th_lock_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_th_lock_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rabin_cmd ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static RThreadFunctionRet rabin_delegate(RThread *th) {
	RIODesc *d = r_io_desc_get (r.io, r.file->fd);
	if (rabin_cmd && r_file_exists (d->name)) {
		char *nptr, *ptr, *cmd = r_sys_cmd_str (rabin_cmd, NULL, NULL);
		ptr = cmd;
		if (ptr) {
			do {
				if (th) {
					r_th_lock_enter (th->user);
				}
				nptr = strchr (ptr, '\n');
				if (nptr) {
					*nptr = 0;
				}
				r_core_cmd (&r, ptr, 0);
				if (nptr) {
					ptr = nptr + 1;
				}
				if (th) {
					r_th_lock_leave (th->user);
				}
			} while (nptr);
		}
		//r_core_cmd (&r, cmd, 0);
		free (rabin_cmd);
		rabin_cmd = NULL;
	}
	if (th) {
		eprintf ("rabin2: done\n");
	}
	return R_TH_STOP;
}