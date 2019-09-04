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
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/  r_io_mmap_check (char const*) ; 
 int /*<<< orphan*/ * r_io_mmap_open (int /*<<< orphan*/ *,char const*,int,int) ; 

__attribute__((used)) static RIODesc *__open(RIO *io, const char *file, int flags, int mode) {
	if (!r_io_mmap_check (file)) {
		return NULL;
	}
	return r_io_mmap_open (io, file, flags, mode);
}