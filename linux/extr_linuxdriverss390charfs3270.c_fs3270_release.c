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
struct raw3270_view {int dummy; } ;
struct fs3270 {scalar_t__ fs_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  kill_pid (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fs3270_release(struct raw3270_view *view)
{
	struct fs3270 *fp;

	fp = (struct fs3270 *) view;
	if (fp->fs_pid)
		kill_pid(fp->fs_pid, SIGHUP, 1);
}