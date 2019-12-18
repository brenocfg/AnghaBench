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
 int /*<<< orphan*/  FREEMEM (void*) ; 

int LZ4_freeHC (void* LZ4HC_Data)
{
    if (!LZ4HC_Data) return 0;  /* support free on NULL */
    FREEMEM(LZ4HC_Data);
    return 0;
}