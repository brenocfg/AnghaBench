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
struct file_lock {int /*<<< orphan*/  fl_fasync; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_MSG ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
lease_break_callback(struct file_lock *fl)
{
	kill_fasync(&fl->fl_fasync, SIGIO, POLL_MSG);
	return false;
}