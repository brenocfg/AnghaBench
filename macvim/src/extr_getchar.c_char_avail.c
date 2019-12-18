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
 int NUL ; 
 int /*<<< orphan*/  no_mapping ; 
 int vpeekc () ; 

int
char_avail()
{
    int	    retval;

    ++no_mapping;
    retval = vpeekc();
    --no_mapping;
    return (retval != NUL);
}