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
 size_t MAXNUM ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  abort () ; 
 void* calloc (size_t,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void *
CALLOC(size_t count, size_t size)
{
    void *p;
    
    if (count >= MAXNUM || size >= MAXNUM) {
        if (size != 0 && count >= SIZE_MAX/size) {
            fprintf(stderr, "[-] alloc too large, aborting\n");
            abort();
        }
    }
    
    p = calloc(count, size);
    if (p == NULL && count * size != 0) {
        fprintf(stderr, "[-] out of memory, aborting\n");
        abort();
    }
    
    return p;
}