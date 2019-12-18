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
struct TYPE_8__ {int /*<<< orphan*/  fd; TYPE_1__* core; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  io; } ;
typedef  TYPE_2__ RIODesc ;
typedef  TYPE_3__ RCoreFile ;

/* Variables and functions */
 TYPE_2__* r_io_desc_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool is_valid_gdb_file(RCoreFile *fh) {
	RIODesc *d = fh && fh->core ? r_io_desc_get (fh->core->io, fh->fd) : NULL;
	return d && strncmp (d->name, "gdb://", 6);
}