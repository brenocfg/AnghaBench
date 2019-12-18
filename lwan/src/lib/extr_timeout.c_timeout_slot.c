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
typedef  int timeout_t ;

/* Variables and functions */
 int WHEEL_BIT ; 
 int /*<<< orphan*/  WHEEL_MASK ; 

__attribute__((used)) static inline int timeout_slot(int wheel, timeout_t expires)
{
    const timeout_t wheel_mask = (timeout_t)WHEEL_MASK;
    const timeout_t slot =
        wheel_mask & ((expires >> (wheel * WHEEL_BIT)) - !!wheel);

    return (int)slot;
}