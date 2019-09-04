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
struct un_t {int un_flags; int /*<<< orphan*/  un_flags_wait; } ;

/* Variables and functions */
 int UN_EMPTY ; 
 int UN_LOW ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dgnc_wake_up_unit(struct un_t *unit)
{
	unit->un_flags &= ~(UN_LOW | UN_EMPTY);
	wake_up_interruptible(&unit->un_flags_wait);
}