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
 int /*<<< orphan*/  copy_executeFileMap (int /*<<< orphan*/ ) ; 
 scalar_t__ datadir_source ; 
 int /*<<< orphan*/  filemap ; 
 int /*<<< orphan*/  libpq_executeFileMap (int /*<<< orphan*/ ) ; 

void
executeFileMap(void)
{
	if (datadir_source)
		copy_executeFileMap(filemap);
	else
		libpq_executeFileMap(filemap);
}