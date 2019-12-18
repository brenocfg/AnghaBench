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
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  data_sync_elevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync_fname_ext (char const*,int,int,int /*<<< orphan*/ ) ; 

void
fsync_fname(const char *fname, bool isdir)
{
	fsync_fname_ext(fname, isdir, false, data_sync_elevel(ERROR));
}