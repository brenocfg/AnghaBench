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
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 void* heap_realloc (void*,size_t) ; 

void *heap_xrealloc(void *buf, size_t size)
{
    void *new_buf = heap_realloc(buf, size);

    if (!new_buf)
    {
        ERR("Out of memory!\n");
        exit(1);
    }

    return new_buf;
}