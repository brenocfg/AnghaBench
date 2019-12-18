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
 char* pg_malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int wal_segment_size_mb ; 

__attribute__((used)) static char *
pretty_wal_size(int segment_count)
{
	int			sz = wal_segment_size_mb * segment_count;
	char	   *result = pg_malloc(14);

	if ((sz % 1024) == 0)
		snprintf(result, 14, "%dGB", sz / 1024);
	else
		snprintf(result, 14, "%dMB", sz);

	return result;
}