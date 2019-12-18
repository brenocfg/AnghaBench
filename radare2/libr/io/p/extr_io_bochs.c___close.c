#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RIODesc ;

/* Variables and functions */
 int /*<<< orphan*/  bochs_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  lprintf (char*) ; 

__attribute__((used)) static int __close(RIODesc *fd) {
	lprintf("io_close\n");
	bochs_close (desc);
	return true;
}