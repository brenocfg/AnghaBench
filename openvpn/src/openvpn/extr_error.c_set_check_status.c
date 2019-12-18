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
 unsigned int x_cs_info_level ; 
 unsigned int x_cs_verbose_level ; 

void
set_check_status(unsigned int info_level, unsigned int verbose_level)
{
    x_cs_info_level = info_level;
    x_cs_verbose_level = verbose_level;
}