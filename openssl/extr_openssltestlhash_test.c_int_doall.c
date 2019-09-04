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
 size_t int_find (int) ; 
 int /*<<< orphan*/ * int_found ; 

__attribute__((used)) static void int_doall(int *v)
{
    int_found[int_find(*v)]++;
}