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

long
mch_get_pid()
{
#ifdef __amigaos4__
    /* This is as close to a pid as we can come. We could use CLI numbers also,
     * but then we would have two different types of process identifiers.
     */
    return((long)FindTask(0));
#else
    return (long)0;
#endif
}