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
 int /*<<< orphan*/ * file_map ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmap_failed ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ sb ; 

__attribute__((used)) static void mmap_cleanup(void)
{
	if (!mmap_failed)
		munmap(file_map, sb.st_size);
	else
		free(file_map);
	file_map = NULL;
}