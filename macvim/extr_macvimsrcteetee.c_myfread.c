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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int getchar () ; 

int
myfread(char *buf, int elsize /*ignored*/, int max, FILE *fp)
{
	int	c;
	int	n = 0;

	while ((n < max) && ((c = getchar()) != EOF))
	{
		*(buf++) = c;
		n++;
		if (c == '\n' || c == '\r')
			break;
	}
	return n;
}