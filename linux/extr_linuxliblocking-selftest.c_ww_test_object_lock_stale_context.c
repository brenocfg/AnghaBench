#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WWAI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WWL (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ o ; 
 int /*<<< orphan*/  t ; 
 int /*<<< orphan*/  t2 ; 

__attribute__((used)) static void ww_test_object_lock_stale_context(void)
{
	WWAI(&t);
	o.ctx = &t2;
	WWL(&o, &t);
}