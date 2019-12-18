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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ read_text (char*,char*,int) ; 
 char* strtok (char*,char const*) ; 

int is_swap_enabled(void)
{
	char buf[PAGE_SIZE];
	const char delim[] = "\n";
	int cnt = 0;
	char *line;

	if (read_text("/proc/swaps", buf, sizeof(buf)) <= 0)
		return -1;

	for (line = strtok(buf, delim); line; line = strtok(NULL, delim))
		cnt++;

	return cnt > 1;
}