#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_8__ {int /*<<< orphan*/  io; TYPE_1__* (* open_at ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* fd_remap ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* fd_get_name ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ RIODesc ;
typedef  TYPE_2__ RIOBind ;

/* Variables and functions */
 int /*<<< orphan*/  R_PERM_RW ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_str_newf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* stub3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RIODesc *cpu_memory_map (RIOBind *iob, RIODesc *desc, ut32 addr,
				ut32 size) {
	char *mstr = r_str_newf ("malloc://%d", size);
	if (desc && iob->fd_get_name (iob->io, desc->fd)) {
		iob->fd_remap (iob->io, desc->fd, addr);
	} else {
		desc = iob->open_at (iob->io, mstr, R_PERM_RW, 0, addr);
	}
	free (mstr);
	return desc;
}