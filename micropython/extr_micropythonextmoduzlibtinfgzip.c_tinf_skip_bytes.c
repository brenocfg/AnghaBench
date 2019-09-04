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
typedef  int /*<<< orphan*/  TINF_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  uzlib_get_byte (int /*<<< orphan*/ *) ; 

void tinf_skip_bytes(TINF_DATA *d, int num)
{
    while (num--) uzlib_get_byte(d);
}