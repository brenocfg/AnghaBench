#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pid; } ;
typedef  int /*<<< orphan*/  RIODesc ;

/* Variables and functions */
 TYPE_1__* desc ; 

__attribute__((used)) static int __getpid(RIODesc *fd) {
	// XXX dont use globals
	return desc ? desc->pid : -1;
#if 0
	// dupe for ? r_io_desc_get_pid (desc);
	if (!desc || !desc->data) {
		return -1;
	}
	RIODescData *iodd = desc->data;
	if (iodd) {
		if (iodd->magic != R_GDB_MAGIC) {
			return -1;
		}
		return iodd->pid;
	}
	return -1;
#endif
}