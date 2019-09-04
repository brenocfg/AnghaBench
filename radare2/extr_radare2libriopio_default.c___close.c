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
 int r_io_def_mmap_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __close(RIODesc *fd) {
	return r_io_def_mmap_close (fd);
}