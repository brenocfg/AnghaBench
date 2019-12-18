#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ b_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bt_dontwrite (TYPE_1__*) ; 
 TYPE_1__* curbuf ; 
 scalar_t__ file_ff_differs (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
curbufIsChanged()
{
    return
#ifdef FEAT_QUICKFIX
	!bt_dontwrite(curbuf) &&
#endif
	(curbuf->b_changed || file_ff_differs(curbuf, TRUE));
}