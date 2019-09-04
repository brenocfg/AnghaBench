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
struct TYPE_2__ {int /*<<< orphan*/  st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehdr_curr ; 
 int /*<<< orphan*/  fd_map ; 
 int /*<<< orphan*/  mmap_failed ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ sb ; 

__attribute__((used)) static void
cleanup(void)
{
	if (!mmap_failed)
		munmap(ehdr_curr, sb.st_size);
	close(fd_map);
}