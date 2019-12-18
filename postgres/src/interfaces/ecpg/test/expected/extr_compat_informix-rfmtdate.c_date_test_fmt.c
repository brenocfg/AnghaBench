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
typedef  int /*<<< orphan*/  date ;

/* Variables and functions */
 int /*<<< orphan*/  check_return (int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int rfmtdate (int /*<<< orphan*/ ,char const*,char*) ; 

__attribute__((used)) static void
date_test_fmt(date d, const char *fmt)
{
	static int i;
	char buf[200];
	int r;

	r = rfmtdate(d, fmt, buf);
	printf("r: %d ", r);
	if (r != 0)
		check_return(r);
	else
		printf("date: %d: %s\n", i++, buf);
}