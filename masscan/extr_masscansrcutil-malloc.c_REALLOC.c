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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 void* realloc (void*,size_t) ; 
 int /*<<< orphan*/  stderr ; 

void *
REALLOC(void *p, size_t size)
{
    p = realloc(p, size);
    
    if (p == NULL) {
        fprintf(stderr, "[-] out of memory, aborting\n");
        abort();
    }
    
    return p;
}