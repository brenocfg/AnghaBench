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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSLOG_ACTION_CLOSE ; 
 int /*<<< orphan*/  SYSLOG_FROM_PROC ; 
 int /*<<< orphan*/  do_syslog (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kmsg_release(struct inode * inode, struct file * file)
{
	(void) do_syslog(SYSLOG_ACTION_CLOSE, NULL, 0, SYSLOG_FROM_PROC);
	return 0;
}