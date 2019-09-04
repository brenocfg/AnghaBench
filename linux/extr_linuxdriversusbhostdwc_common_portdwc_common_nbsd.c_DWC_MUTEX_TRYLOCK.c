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
struct lock {int dummy; } ;
typedef  int /*<<< orphan*/  dwc_mutex_t ;

/* Variables and functions */
 int LK_EXCLUSIVE ; 
 int LK_NOWAIT ; 
 int lockmgr (struct lock*,int,int /*<<< orphan*/ *) ; 

int DWC_MUTEX_TRYLOCK(dwc_mutex_t *mutex)
{
	int status;

	status = lockmgr((struct lock *)mutex, LK_EXCLUSIVE | LK_NOWAIT, NULL);
	return status == 0;
}