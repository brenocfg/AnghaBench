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
typedef  int /*<<< orphan*/  RC4_INT ;

/* Variables and functions */

const char *RC4_options(void)
{
    if (sizeof(RC4_INT) == 1)
        return "rc4(char)";
    else
        return "rc4(int)";
}