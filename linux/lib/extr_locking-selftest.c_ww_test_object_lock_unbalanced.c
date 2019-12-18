#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ acquired; } ;

/* Variables and functions */
 int /*<<< orphan*/  WWAF (TYPE_1__*) ; 
 int /*<<< orphan*/  WWAI (TYPE_1__*) ; 
 int /*<<< orphan*/  WWL (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  WWU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o ; 
 TYPE_1__ t ; 

__attribute__((used)) static void ww_test_object_lock_unbalanced(void)
{
	WWAI(&t);
	WWL(&o, &t);
	t.acquired = 0;
	WWU(&o);
	WWAF(&t);
}