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
struct mp_cancel {int dummy; } ;

/* Variables and functions */
 scalar_t__ mp_cancel_test (struct mp_cancel*) ; 
 int /*<<< orphan*/  trigger_locked (struct mp_cancel*) ; 

__attribute__((used)) static void retrigger_locked(struct mp_cancel *c)
{
    if (mp_cancel_test(c))
        trigger_locked(c);
}