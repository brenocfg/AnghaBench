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
 int /*<<< orphan*/  check_return (int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int rfmtlong (long,char const*,char*) ; 

__attribute__((used)) static void
fmtlong(long lng, const char *fmt)
{
	static int i;
	int r;
	char buf[30];

	r = rfmtlong(lng, fmt, buf);
	printf("r: %d ", r);
	if (r == 0)
	{
		printf("%d: %s (fmt was: %s)\n", i++, buf, fmt);
	}
	else
		check_return(r);
}