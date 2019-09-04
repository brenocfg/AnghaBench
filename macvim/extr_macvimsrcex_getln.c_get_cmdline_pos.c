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
struct cmdline_info {int cmdpos; } ;

/* Variables and functions */
 struct cmdline_info* get_ccline_ptr () ; 

int
get_cmdline_pos()
{
    struct cmdline_info *p = get_ccline_ptr();

    if (p == NULL)
	return -1;
    return p->cmdpos;
}