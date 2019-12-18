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
typedef  char* LPSTR ;

/* Variables and functions */

__attribute__((used)) static inline int enter_shift(LPSTR out, int c)
{
    if (out)
    {
        out[c] = 0x1b;
        out[c+1] = '$';
        out[c+2] = 'B';
    }
    return 3;
}