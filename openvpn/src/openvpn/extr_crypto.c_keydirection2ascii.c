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
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int KEY_DIRECTION_BIDIRECTIONAL ; 
 int KEY_DIRECTION_INVERSE ; 
 int KEY_DIRECTION_NORMAL ; 

const char *
keydirection2ascii(int kd, bool remote, bool humanreadable)
{
    if (kd == KEY_DIRECTION_BIDIRECTIONAL)
    {
        if (humanreadable)
        {
            return "not set";
        }
        else
        {
            return NULL;
        }
    }
    else if (kd == KEY_DIRECTION_NORMAL)
    {
        return remote ? "1" : "0";
    }
    else if (kd == KEY_DIRECTION_INVERSE)
    {
        return remote ? "0" : "1";
    }
    else
    {
        ASSERT(0);
    }
    return NULL; /* NOTREACHED */
}