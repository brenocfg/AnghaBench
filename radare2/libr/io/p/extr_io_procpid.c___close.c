#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RIODesc ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_DETACH ; 
 int /*<<< orphan*/  RIOPROCPID_PID (TYPE_1__*) ; 
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __close(RIODesc *fd) {
	int ret = ptrace (PTRACE_DETACH, RIOPROCPID_PID (fd), 0, 0);
	R_FREE (fd->data);
	return ret;
}