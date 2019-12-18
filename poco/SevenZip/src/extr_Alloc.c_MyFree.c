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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int g_allocCount ; 
 int /*<<< orphan*/  stderr ; 

void MyFree(void *address)
{
  #ifdef _SZ_ALLOC_DEBUG
  if (address != 0)
    fprintf(stderr, "\nFree; count = %10d,  addr = %8X", --g_allocCount, (unsigned)address);
  #endif
  free(address);
}