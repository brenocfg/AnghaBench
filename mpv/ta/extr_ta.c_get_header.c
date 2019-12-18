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
struct ta_header {int dummy; } ;

/* Variables and functions */
 struct ta_header* PTR_TO_HEADER (void*) ; 
 int /*<<< orphan*/  ta_dbg_check_header (struct ta_header*) ; 

__attribute__((used)) static struct ta_header *get_header(void *ptr)
{
    struct ta_header *h = ptr ? PTR_TO_HEADER(ptr) : NULL;
    ta_dbg_check_header(h);
    return h;
}