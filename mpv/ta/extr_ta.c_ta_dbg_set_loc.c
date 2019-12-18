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
struct ta_header {char const* name; } ;

/* Variables and functions */
 struct ta_header* get_header (void*) ; 

void *ta_dbg_set_loc(void *ptr, const char *loc)
{
    struct ta_header *h = get_header(ptr);
    if (h)
        h->name = loc;
    return ptr;
}