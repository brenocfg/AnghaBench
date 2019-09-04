#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {long target_pages; long current_pages; } ;

/* Variables and functions */
 TYPE_1__ balloon_stats ; 

__attribute__((used)) static long current_credit(void)
{
	return balloon_stats.target_pages - balloon_stats.current_pages;
}