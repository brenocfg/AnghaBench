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
 int /*<<< orphan*/  printf (char*,...) ; 
 int rdatestr (int /*<<< orphan*/ ,char*) ; 
 int rstrdate (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
date_test_strdate(const char *input)
{
	static int i;
	date d;
	int r, q;
	char dbuf[11];

	r = rstrdate(input, &d);
	printf("r: %d ", r);
	if (r == 0)
	{
		q = rdatestr(d, dbuf);
		printf("q: %d ", q);
		if (q == 0)
		{
			printf("date %d: %s\n", i++, dbuf);
		}
		else
			printf("\n");
	}
	else
		check_return(r);
}