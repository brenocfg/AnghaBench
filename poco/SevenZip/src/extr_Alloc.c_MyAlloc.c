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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  g_allocCount ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  stderr ; 

void *MyAlloc(size_t size)
{
  if (size == 0)
    return 0;
  #ifdef _SZ_ALLOC_DEBUG
  {
    void *p = malloc(size);
    fprintf(stderr, "\nAlloc %10d bytes, count = %10d,  addr = %8X", size, g_allocCount++, (unsigned)p);
    return p;
  }
  #else
  return malloc(size);
  #endif
}