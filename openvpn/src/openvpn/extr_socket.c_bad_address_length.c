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
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int,int) ; 

void
bad_address_length(int actual, int expected)
{
    msg(M_FATAL, "ERROR: received strange incoming packet with an address length of %d -- we only accept address lengths of %d.",
        actual,
        expected);
}