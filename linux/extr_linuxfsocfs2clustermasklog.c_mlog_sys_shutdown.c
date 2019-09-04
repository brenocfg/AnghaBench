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
 int /*<<< orphan*/  kset_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_kset ; 

void mlog_sys_shutdown(void)
{
	kset_unregister(&mlog_kset);
}