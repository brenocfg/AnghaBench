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

/* Variables and functions */

__attribute__((used)) static void check_choice(int dir, int val, bool *found, int *best, int choice)
{
    if ((dir == -1 && (!(*found) || choice > (*best)) && choice < val) ||
        (dir == +1 && (!(*found) || choice < (*best)) && choice > val))
    {
        *found = true;
        *best = choice;
    }
}