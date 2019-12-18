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
typedef  int /*<<< orphan*/  process_file_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  recurse_dir (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
traverse_datadir(const char *datadir, process_file_callback_t callback)
{
	recurse_dir(datadir, NULL, callback);
}