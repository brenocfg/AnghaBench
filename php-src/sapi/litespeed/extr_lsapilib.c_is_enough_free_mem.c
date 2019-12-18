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
 int* s_avail_pages ; 
 int s_min_avail_pages ; 
 int s_total_pages ; 

int is_enough_free_mem()
{
#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
    //minimum 1GB or 10% available free memory
    return (*s_avail_pages > s_min_avail_pages
            || (*s_avail_pages * 10) / s_total_pages > 0);
#endif
    return 1;
}