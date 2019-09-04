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
struct w1_slave {int /*<<< orphan*/ * family_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  THERM_REFCNT (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ ) ; 
 int atomic_sub_return (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void w1_therm_remove_slave(struct w1_slave *sl)
{
	int refcnt = atomic_sub_return(1, THERM_REFCNT(sl->family_data));

	while (refcnt) {
		msleep(1000);
		refcnt = atomic_read(THERM_REFCNT(sl->family_data));
	}
	kfree(sl->family_data);
	sl->family_data = NULL;
}