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
struct charger_manager {scalar_t__ emergency_stop; } ;

/* Variables and functions */
 int EAGAIN ; 
 int try_charger_enable (struct charger_manager*,int) ; 

__attribute__((used)) static int try_charger_restart(struct charger_manager *cm)
{
	int err;

	if (cm->emergency_stop)
		return -EAGAIN;

	err = try_charger_enable(cm, false);
	if (err)
		return err;

	return try_charger_enable(cm, true);
}