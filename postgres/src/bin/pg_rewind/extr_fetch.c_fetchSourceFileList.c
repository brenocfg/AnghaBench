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

/* Variables and functions */
 scalar_t__ datadir_source ; 
 int /*<<< orphan*/  libpqProcessFileList () ; 
 int /*<<< orphan*/  process_source_file ; 
 int /*<<< orphan*/  traverse_datadir (scalar_t__,int /*<<< orphan*/ *) ; 

void
fetchSourceFileList(void)
{
	if (datadir_source)
		traverse_datadir(datadir_source, &process_source_file);
	else
		libpqProcessFileList();
}