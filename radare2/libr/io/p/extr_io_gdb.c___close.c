#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RIODesc ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  gdbr_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbr_disconnect (int /*<<< orphan*/ ) ; 
 TYPE_2__* riogdb ; 

__attribute__((used)) static int __close(RIODesc *fd) {
	if (fd) {
		R_FREE (fd->name);
	}
	gdbr_disconnect (desc);
	gdbr_cleanup (desc);
	if (riogdb) {	//TODO is there a less band-aid fix to do this?
		riogdb->data = NULL;
	}
	R_FREE (desc);
	return -1;
}