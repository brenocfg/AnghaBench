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
 int /*<<< orphan*/  TRACE (char*,...) ; 
 unsigned int min (unsigned int,int) ; 

__attribute__((used)) static void dump_bytecode(void *data, unsigned int size)
{
    unsigned int *bytecode = (unsigned int *)data;
    unsigned int i, j, n;

    size /= sizeof(*bytecode);
    i = 0;
    while (i < size)
    {
        n = min(size - i, 8);
        for (j = 0; j < n; ++j)
            TRACE("0x%08x,", bytecode[i + j]);
        i += n;
        TRACE("\n");
    }
}