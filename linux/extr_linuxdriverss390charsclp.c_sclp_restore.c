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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCLP_PM_EVENT_RESTORE ; 
 int sclp_undo_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sclp_restore(struct device *dev)
{
	return sclp_undo_suspend(SCLP_PM_EVENT_RESTORE);
}