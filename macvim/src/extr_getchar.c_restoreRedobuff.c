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
 int /*<<< orphan*/  free_buff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  old_redobuff ; 
 int /*<<< orphan*/  redobuff ; 
 scalar_t__ save_level ; 
 int /*<<< orphan*/  save_old_redobuff ; 
 int /*<<< orphan*/  save_redobuff ; 

void
restoreRedobuff()
{
    if (--save_level == 0)
    {
	free_buff(&redobuff);
	redobuff = save_redobuff;
	free_buff(&old_redobuff);
	old_redobuff = save_old_redobuff;
    }
}