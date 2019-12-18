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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int jbd2__journal_restart (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int jbd2_journal_restart(handle_t *handle, int nblocks)
{
	return jbd2__journal_restart(handle, nblocks, GFP_NOFS);
}