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
typedef  int time_t ;
struct stat {int st_mtime; } ;

/* Variables and functions */
 scalar_t__ os_stat (char*,struct stat*) ; 

time_t get_modified_timestamp(char *filename)
{
	struct stat stats;

	// stat is apparently terrifying and horrible, but we only call it once
	// every second at most.
	if (os_stat(filename, &stats) != 0)
		return -1;

	return stats.st_mtime;
}